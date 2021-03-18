#include "linevisitor.h"

LineVisitor::LineVisitor(unsigned int pointNumber, unsigned int offset, unsigned int steps) : AbstractVisitor (pointNumber, offset)
{
    if(pointNumber >= 2)
    {
        unsigned int components = pointNumber - 1;
        deltaT = 1.0f / steps * components;
    }
    else {
          deltaT = 1.0f / steps;
    }

    currentPoint = offset;
    tInComponent = 0.0;
}

const Point* LineVisitor::next(std::vector<Point>& points)
{
    if(currentPoint + 1 >= offset + pointNumber)
    {
        return nullptr;
    }

    p = linearCombination(points[currentPoint], points[currentPoint + 1], tInComponent);
    p.enableLaser = points[currentPoint].enableLaser;

    tInComponent += deltaT;
    if(!p.enableLaser)
    {
        tInComponent += deltaT;
    }

    if(tInComponent > 1.0f)
    {
        tInComponent = 0.0;
        currentPoint ++;
    }

    return &p;
}
