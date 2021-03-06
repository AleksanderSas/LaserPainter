#include "shapecollection.h"
#include <iostream>
#include <fstream>
#include "beziervisitor.h"
#include "circlevisitor.h"
#include "linevisitor.h"

ShapeCollection::ShapeCollection()
{

}

ShapeCollection::~ShapeCollection()
{
    clear();
}

void ShapeCollection::Add(unsigned int x, unsigned int y, ShapeType type, bool enableLaser, int position)
{
    Point p(x, y, type, enableLaser);
    if(position < 0)
    {
        points.push_back(p);
    }else
    {
        points.insert(points.begin() + position, p);
    }
}

std::vector<Point>::iterator ShapeCollection::getPointIterator(int x, int y)
{
    unsigned int currentDist = 9999;
    std::vector<Point>::iterator itr = points.end();
    for(auto iter = points.begin(); iter != points.end(); iter++)
    {
        unsigned int dist = (iter->x - x) * (iter->x - x) + (iter->y - y) * (iter->y - y);
        if(dist < 1600 && dist < currentDist)
        {
            itr = iter;
            currentDist = dist;
        }
    }
    return itr;
}

std::pair<int, Point> ShapeCollection::deletePoint(unsigned int x, unsigned int y)
{
    Point p;
    auto iter = getPointIterator(x, y);
    if(iter != points.end())
    {
        p = *iter;
        points.erase(iter);
    }
    return std::pair<int, Point>(iter - points.begin(), p);
}

Point* ShapeCollection::getPoint(unsigned int x, unsigned int y)
{
    auto iter = getPointIterator(x, y);
    return iter != points.end()? &(*iter) : nullptr;
}

std::pair<bool, Point*> ShapeCollection::getOrAddPoint(unsigned int x, unsigned int y, ShapeType type)
{
    auto iter = getPointIterator(x, y);
    if(iter != points.end())
    {
        return std::pair<bool, Point*>(false, &(*iter));
    }
    Add(x, y, type, true);
    return std::pair<bool, Point*>(true, &points[points.size() - 1]);
}

void ShapeCollection::insertPointBefore(Point &p)
{
    auto iter = getPointIterator(p.x, p.y);
    points.insert(iter, p);
}

void ShapeCollection::insertPointBefore(unsigned int x, unsigned int y, ShapeType type)
{
    Point p(x, y + 100, type, true);
    auto iter = getPointIterator(x, y);
    points.insert(iter, p);
}

void ShapeCollection::loadV1(std::ifstream &myfile)
{
    while(myfile.good())
    {
        unsigned int x, y;
        myfile >> x;
        myfile >> y;
        Add(x, y, ShapeType::BEZIER, true);
    }
}

void ShapeCollection::loadV2(std::ifstream &myfile)
{
    while(myfile.good())
    {
        unsigned int x, y, lineType;
        myfile >> lineType;
        myfile >> x;
        myfile >> y;
        Add(x, y, (ShapeType)lineType, true);
    }
}

void ShapeCollection::loadV3(std::ifstream &myfile)
{
    while(myfile.good())
    {
        unsigned int x, y, lineType;
        bool enableLaser;
        myfile >> lineType;
        myfile >> x;
        myfile >> y;
        myfile >> enableLaser;
        Add(x, y, (ShapeType)lineType, enableLaser);
    }
}

void ShapeCollection::load(const char* file)
{
    std::ifstream myfile;
    myfile.open (file);
    std::string version;
    myfile >> version;
    if(version != "V1" && version != "V2" && version != "V3")
    {
        throw "only V1, V2 and V3 standards are supported";
    }
    if(version == "V1")
        loadV1(myfile);
    if(version == "V2")
        loadV2(myfile);
    if(version == "V3")
        loadV3(myfile);
    myfile.close();
}

void ShapeCollection::save(const char* file)
{
    std::ofstream myfile;
    myfile.open (file);
    myfile << "V3" << std::endl;
    for(Point &p : points)
    {
        myfile << p.type << " " << p.x << " " << p.y << " " << p.enableLaser << std::endl;
    }
    myfile.close();
}

void ShapeCollection::clear()
{
    points.clear();
}

AbstractVisitor* GetNextVisitor(ShapeType type, unsigned int pointNumber, unsigned int offset, unsigned int steps)
{
    switch(type)
    {
        case ShapeType::LINE:
            return  new LineVisitor(pointNumber, offset, steps);
        case ShapeType::BEZIER:
            return  new BezierVisitor(pointNumber, offset, steps);
        case ShapeType::CIRCLE:
            return  new CircleVisitor(pointNumber, offset, steps);
    }
    return nullptr;
}

unsigned int GetShapeFactor(ShapeType type)
{
    switch(type)
    {
        case ShapeType::LINE:
            return 1;
        case ShapeType::BEZIER:
            return 1;
        case ShapeType::CIRCLE:
            return 4;
    }
    return 0;
}

bool ShapeCollection::SetNextVisitor(bool firstVisitor, unsigned int steps)
{
    if(iter == points.end())
        return false;

    unsigned int pointNumber = firstVisitor? 1 : 2;
    ShapeType type = ShapeType::BEZIER;
    type = (*iter).type;
    while(++iter != points.end() && (*iter).type == type)
    {
        pointNumber++;
        type = (*iter).type;
    }

    unsigned int offset = iter - points.begin() - pointNumber;
    unsigned int visitorSteps = steps * pointNumber * GetShapeFactor(type) / points.size();
    currectVisitor = GetNextVisitor(type, pointNumber, offset, visitorSteps);
    return true;
}

const Point* ShapeCollection::next(unsigned int steps)
{
    if(currectVisitor == nullptr)
    {
        iter = points.begin();
        if(!SetNextVisitor(true, steps))
            return  nullptr;
    }

    const Point* p = currectVisitor->next(points);
    while(p == nullptr)
    {
        delete  currectVisitor;
        currectVisitor = nullptr;
        if(!SetNextVisitor(false, steps))
            return  nullptr;
        p = currectVisitor->next(points);
    }
    return p;
}
