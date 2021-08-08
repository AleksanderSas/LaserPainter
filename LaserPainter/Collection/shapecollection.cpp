#include "shapecollection.h"
#include <iostream>
#include <fstream>
#include "Visitors/beziervisitor.h"
#include "Visitors/circlevisitor.h"
#include "Visitors/linevisitor.h"
#include "Visitors/halfcirclevisitor.h"

ShapeCollection::ShapeCollection()
{
    insertPosition = points.begin();
}

ShapeCollection::~ShapeCollection()
{
    clear();
}

void ShapeCollection::Add(float x, float y, ShapeType type, bool enableLaser, bool wait, int position)
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

std::vector<Point>::iterator ShapeCollection::getPointIterator(float x, float y)
{
    float currentDist = 9999.0f;
    std::vector<Point>::iterator itr = points.end();
    for(auto iter = points.begin(); iter != points.end(); iter++)
    {
        float dist = (iter->x - x) * (iter->x - x) + (iter->y - y) * (iter->y - y);
        if(dist < 1600.0f && dist < currentDist)
        {
            itr = iter;
            currentDist = dist;
        }
    }
    return itr;
}

std::pair<int, Point> ShapeCollection::deletePoint(int x, int y)
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

Point* ShapeCollection::getPoint(int x, int y)
{
    auto iter = getPointIterator(x, y);
    return iter != points.end()? &(*iter) : nullptr;
}

std::pair<bool, Point*> ShapeCollection::getOrAddPoint(int x, int y, ShapeType type)
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
        case ShapeType::HALF_CIRCLE:
            return  new HalfCircleVisitor(pointNumber, offset);
    }
    return nullptr;
}

void ShapeCollection::restart()
{
    if(currentVisitor != nullptr)
    {
        delete currentVisitor;
        currentVisitor = nullptr;
    }
    insertPosition = points.begin();
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
    currentVisitor = GetNextVisitor(type, pointNumber, offset);
    return true;
}

const PointWithMetadata* ShapeCollection::next(unsigned int stepsSize)
{
    if(currentVisitor == nullptr)
    {
        iter = points.begin();
        if(!SetNextVisitor(true))
            return  nullptr;
    }

    const PointWithMetadata* p = currentVisitor->next(points, stepsSize);
    while(p == nullptr)
    {
        delete  currentVisitor;
        currentVisitor = nullptr;
        if(!SetNextVisitor(false))
            return  nullptr;
        p = currentVisitor->next(points, stepsSize);
    }
    return p;
}
