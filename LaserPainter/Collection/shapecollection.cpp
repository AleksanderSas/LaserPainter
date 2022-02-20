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
    previousPoint = Point(0, 0);
    previousPreviousPoint = Point(0, 0);
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

SelectedPoint ShapeCollection::getOrAddPoint(int x, int y, ShapeType type)
{
    auto iter = getPointIterator(x, y);
    if(iter != points.end())
    {
        return SelectedPoint(false, iter - points.begin(), &(*iter));
    }
    Add(x, y, type, true, false);
    return SelectedPoint(true, insertPosition - points.begin() - 1, &(*(insertPosition - 1)));
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

ComponentPoints ShapeCollection::getPointsFromComponent(unsigned int idx)
{
    unsigned int start = 0;
    while(idx - start > 0 && points[idx - start].type == points[idx].type)
    {
        start++;
    }
    AbstractVisitor* visitor = GetNextVisitor(points[idx].type, 0, 0);
    unsigned int pointPerComponent = visitor->getPointPerComponent();
    delete visitor;
    unsigned int componentsBefore = start > 0? ((start - 1) / (pointPerComponent - 1)) : 0;
    start = idx - start + componentsBefore * (pointPerComponent - 1);

    unsigned int end = 0;
    while(idx + end + 1 < points.size() && points[idx + end + 1].type == points[idx + 1].type)
    {
        end++;
    }
    visitor = GetNextVisitor(points[idx + end].type, 0, 0);
    pointPerComponent = visitor->getPointPerComponent();
    delete visitor;
    unsigned int componentAfter = end > 0? ((end- 1) / (pointPerComponent - 1)) : 0;
    end = idx + end - componentAfter * (pointPerComponent - 1);
    return ComponentPoints
    (
        start,
        (end - start > pointPerComponent)? end - pointPerComponent + 1 : start,
        end
    );
}

int ShapeCollection::validate()
{
    auto iter = points.begin();
    if(iter == points.end()) return -1;
    ShapeType shapeType = iter->type;
    unsigned int pointsPerComponent = 1;
    AbstractVisitor* visitor = GetNextVisitor(shapeType, 0, 0);
    pointsPerComponent = visitor->getPointPerComponent();
    delete visitor;
    int pointWithTheSameType = 0;
    iter++;

    while(iter != points.end())
    {
        if(shapeType != iter->type)
        {
            if(pointWithTheSameType < pointsPerComponent - 2 || (pointWithTheSameType % (pointsPerComponent - 1)) != 0)
            {
                return iter - points.begin() - 1;
            }
            pointWithTheSameType = 1;
            shapeType = iter->type;
            visitor = GetNextVisitor(shapeType, 0, 0);
            pointsPerComponent = visitor->getPointPerComponent();
            delete visitor;
        }
        else
        {
            pointWithTheSameType++;
        }
        iter++;
    }
    return (pointWithTheSameType >= pointsPerComponent - 2 && (pointWithTheSameType % (pointsPerComponent - 1)) == 0)? -1 : points.size() - 1;
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

const PointWithMetadata* ShapeCollection::next(unsigned int stepsSize, int curvatureLevel)
{
    if(currentVisitor == nullptr)
    {
        iter = points.begin();
        if(!SetNextVisitor(true))
            return  nullptr;
    }

    const PointWithMetadata* p = currentVisitor->next(points, stepsSize, previousPoint, previousPreviousPoint, curvatureLevel);
    while(p == nullptr)
    {
        delete  currentVisitor;
        currentVisitor = nullptr;
        if(!SetNextVisitor(false))
            return  nullptr;
        p = currentVisitor->next(points, stepsSize, previousPoint, previousPreviousPoint, curvatureLevel);
    }
    previousPreviousPoint = previousPoint;
    previousPoint = p->point;
    return p;
}

SelectedPoint::SelectedPoint(bool isAdded, int idx, Point* point):
    isAdded(isAdded), idx(idx), point(point)
{}

ComponentPoints::ComponentPoints(int prev,int current, int end):
    previousComponentStartIdx(prev), currentComponentStartIdx(current), currentComponentEndIdx(end)
{}
