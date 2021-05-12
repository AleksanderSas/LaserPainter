#include "shapecollection.h"
#include <iostream>
#include <fstream>
#include "beziervisitor.h"
#include "circlevisitor.h"
#include "linevisitor.h"

ShapeCollection::ShapeCollection()
{
    insertPosition = points.begin();
}

ShapeCollection::~ShapeCollection()
{
    clear();
}

void ShapeCollection::Add(unsigned int x, unsigned int y, ShapeType type, bool enableLaser, bool wait, int position)
{
    Point p(x, y, type, enableLaser, wait);
    if(position < 0)
    {
        insertPosition = points.insert(insertPosition, p);
        insertPosition++;
    }else
    {
        insertPosition = points.insert(points.begin() + position, p);
        insertPosition++;
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
        insertPosition = points.erase(iter);
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
    Add(x, y, type, true, false);
    return std::pair<bool, Point*>(true, &(*(insertPosition - 1)));
}

void ShapeCollection::insertPointAfter(Point &p)
{
    auto iter = getPointIterator(p.x, p.y);
    if(iter != points.end())
    {
        iter++;
    }
    p.y += 100;
    insertPosition = points.insert(iter, p);
    insertPosition++;
}

void ShapeCollection::loadV2(std::ifstream &myfile)
{
    while(myfile.good())
    {
        unsigned int x, y, lineType;
        myfile >> lineType;
        myfile >> x;
        myfile >> y;
        Add(x, y, (ShapeType)lineType, true, false);
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
        Add(x, y, (ShapeType)lineType, enableLaser, false);
    }
}

void ShapeCollection::loadV4(std::ifstream &myfile)
{
    while(myfile.good())
    {
        unsigned int x, y, lineType;
        bool enableLaser, wait;
        myfile >> lineType;
        myfile >> x;
        myfile >> y;
        myfile >> enableLaser;
        myfile >> wait;
        Add(x, y, (ShapeType)lineType, enableLaser, wait);
    }
}

void ShapeCollection::load(const char* file)
{
    std::ifstream myfile;
    myfile.open (file);
    std::string version;
    myfile >> version;
    if(version != "V4" && version != "V2" && version != "V3")
    {
        throw "only V2, V3 and V4 standards are supported";
    }

    if(version == "V2")
        loadV2(myfile);
    if(version == "V3")
        loadV3(myfile);
    if(version == "V3")
        loadV3(myfile);
    if(version == "V4")
        loadV4(myfile);
    myfile.close();
}

void ShapeCollection::save(const char* file)
{
    std::ofstream myfile;
    myfile.open (file);
    myfile << "V4" << std::endl;
    for(Point &p : points)
    {
        myfile << p.type << " " << p.x << " " << p.y << " " << p.enableLaser << " " << p.wait << std::endl;
    }
    myfile.close();
}

void ShapeCollection::clear()
{
    points.clear();
    insertPosition = points.begin();
}

AbstractVisitor* GetNextVisitor(ShapeType type, unsigned int pointNumber, unsigned int offset)
{
    switch(type)
    {
        case ShapeType::LINE:
            return  new LineVisitor(pointNumber, offset);
        case ShapeType::BEZIER:
            return  new BezierVisitor(pointNumber, offset);
        case ShapeType::CIRCLE:
            return  new CircleVisitor(pointNumber, offset);
    }
    return nullptr;
}

bool ShapeCollection::SetNextVisitor(bool firstVisitor)
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
    currectVisitor = GetNextVisitor(type, pointNumber, offset);
    return true;
}

const PointWithMetadata* ShapeCollection::next(unsigned int stepsSize)
{
    if(currectVisitor == nullptr)
    {
        iter = points.begin();
        if(!SetNextVisitor(true))
            return  nullptr;
    }

    const PointWithMetadata* p = currectVisitor->next(points, stepsSize);
    while(p == nullptr)
    {
        delete  currectVisitor;
        currectVisitor = nullptr;
        if(!SetNextVisitor(false))
            return  nullptr;
        p = currectVisitor->next(points, stepsSize);
    }
    return p;
}
