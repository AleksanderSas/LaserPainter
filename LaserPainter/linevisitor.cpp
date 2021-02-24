#include "linevisitor.h"

LineVisitor::LineVisitor(Line* line, int steps) : line(line)
{
    if(line->pointNumber >= 2)
    {
        unsigned int components = line->pointNumber - 1;
        deltaT = 1.0f / steps * components;
    }
    else {
          deltaT = 1.0f / steps;
    }

    currentPoint = line->offset;
    tInComponent = 0.0;
}

static Point linearCombination(Point& p1, Point& p2, float t)
{
    Point p;
    p.x = (1.0 - t) * p1.x + t * p2.x;
    p.y = (1.0 - t) * p1.y + t * p2.y;
    return p;
}

const Point* LineVisitor::next(std::vector<Point>& points)
{
    if(currentPoint + 1 >= line->offset + line->pointNumber)
    {
        return nullptr;
    }

    p = linearCombination(points[currentPoint], points[currentPoint + 1], tInComponent);
    tInComponent += deltaT;

    if(tInComponent > 1.0f)
    {
        tInComponent = 0.0;
        currentPoint ++;
    }

    return &p;
}
