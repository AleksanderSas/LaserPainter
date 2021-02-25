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

void ShapeCollection::Add(unsigned int x, unsigned int y, ShapeType type)
{
    Point p;
    p.x = x;
    p.y = y;
    p.type = type;
    points.push_back(p);
}

void ShapeCollection::deletePoint(unsigned int x, unsigned int y, unsigned int squerDis)
{
    unsigned int idx = 0;
    for(auto iter = points.begin(); iter != points.end(); iter++)
    {
        unsigned int dist = (iter->x - x) * (iter->x - x) + (iter->y - y) * (iter->y - y);
        if(dist < squerDis)
        {
            points.erase(iter);
            idx = iter - points.begin() + 1;
            break;
        }
    }
}

Point* ShapeCollection::getPoint(unsigned int x, unsigned int y, unsigned int squerDis)
{
    for(Point& p : points)
    {
        unsigned int dist = (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y);
        if(dist < squerDis)
            return &p;
    }
    return nullptr;
}

Point* ShapeCollection::getOrAddPoint(unsigned int x, unsigned int y, ShapeType type, unsigned int squerDis)
{
    for(Point& p : points)
    {
        unsigned int dist = (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y);
        if(dist < squerDis)
            return &p;
    }
    Add(x, y, type);
    return &points[points.size() - 1];
}

void ShapeCollection::loadV1(std::ifstream &myfile)
{
    while(myfile.good())
    {
        unsigned int x, y;
        myfile >> x;
        myfile >> y;
        Add(x, y, ShapeType::BEZIER);
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
        Add(x, y, (ShapeType)lineType);
    }
}

void ShapeCollection::load(const char* file)
{
    std::ifstream myfile;
    myfile.open (file);
    std::string version;
    myfile >> version;
    if(version != "V1" && version != "V2")
    {
        throw "only V1 and V2 standards are supported";
    }
    if(version == "V1")
        loadV1(myfile);
    if(version == "V2")
        loadV2(myfile);
    myfile.close();
}

void ShapeCollection::save(const char* file)
{
    std::ofstream myfile;
    myfile.open (file);
    myfile << "V2" << std::endl;
    for(Point &p : points)
    {
        myfile << p.type << " " << p.x << " " << p.y << std::endl;
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
}

unsigned int GetShapeFactor(ShapeType type)
{
    switch(type)
    {
        case ShapeType::LINE:
            return 2;
        case ShapeType::BEZIER:
            return 1;
        case ShapeType::CIRCLE:
            return 4;
    }
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
