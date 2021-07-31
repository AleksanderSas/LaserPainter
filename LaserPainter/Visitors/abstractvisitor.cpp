#include "abstractvisitor.h"
#include "Collection/shapecollection.h"

AbstractVisitor::AbstractVisitor(unsigned int pointNumber, unsigned int offset, unsigned int pointsPerComponent) :
    pointNumber(pointNumber),
    offset(offset),
    tInComponent(0.0f),
    deltaT(-1.0f),
    currentPoint(offset),
    pointsPerComponent(pointsPerComponent)
{
}

AbstractVisitor::~AbstractVisitor()
{
}

Point linearCombination(Point& p1, Point& p2, float t)
{
    Point p;
    p.x = (1.0f - t) * p1.x + t * p2.x;
    p.y = (1.0f - t) * p1.y + t * p2.y;
    return p;
}

//nullpth is returned when whole sequence is visited
const PointWithMetadata* AbstractVisitor::next(std::vector<Point>& points, unsigned int stepsSize)
{
    if(currentPoint + pointsPerComponent - 1 >= offset + pointNumber)
    {
        return nullptr;
    }
    if(deltaT < 0)
    {
        deltaT = getComponentDelta(points, stepsSize);
    }

    p.isNextComponent = tInComponent == 0.0f;

    if(tInComponent > 1.0f)
    {
        tInComponent = 1.0f;
        p.point = compute(points);
        tInComponent = 0.0;
        currentPoint += pointsPerComponent - 1;
        deltaT = getComponentDelta(points, stepsSize);
    }
    else {
        p.point = compute(points);
        tInComponent += deltaT;
        if(!p.point.enableLaser)
        {
            tInComponent += deltaT;
        }
    }
    p.point.enableLaser = points[currentPoint].enableLaser;
    p.isNextComponent &= points[currentPoint].wait;
    return &p;
}
