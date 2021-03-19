#include "abstractvisitor.h"
#include "shapecollection.h"

AbstractVisitor::AbstractVisitor(unsigned int pointNumber, unsigned int offset, unsigned int pointsPerComponent) :
    pointNumber(pointNumber),
    offset(offset),
    pointsPerComponent(pointsPerComponent),
    deltaT(-1.0f)
{
}

AbstractVisitor::~AbstractVisitor()
{
}

Point linearCombination(Point& p1, Point& p2, float t)
{
    Point p;
    p.x = (1.0 - t) * p1.x + t * p2.x;
    p.y = (1.0 - t) * p1.y + t * p2.y;
    return p;
}

const Point* AbstractVisitor::next(std::vector<Point>& points, unsigned int stepsSize)
{
    if(currentPoint + pointsPerComponent - 1 >= offset + pointNumber)
    {
        return nullptr;
    }
    if(deltaT < 0)
    {
        deltaT = getComponentDelta(points, stepsSize);
    }

    p = compute(points);
    p.enableLaser = points[currentPoint].enableLaser;

    tInComponent += deltaT;
    if(!p.enableLaser)
    {
        tInComponent += deltaT;
    }

    if(tInComponent > 1.0f)
    {
        tInComponent = 0.0;
        currentPoint += pointsPerComponent - 1;
        deltaT = getComponentDelta(points, stepsSize);
    }

    return &p;
}
