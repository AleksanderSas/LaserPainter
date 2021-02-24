#include "circlevisitor.h"
#include "math.h"

CircleVisitor::CircleVisitor(Circle* circle, unsigned int steps) : circle(circle)
{
    if(circle->pointNumber >= 2)
    {
        unsigned int components = circle->pointNumber - 1;
        deltaT = 1.0f / steps * components;
    }
    else {
          deltaT = 1.0f / steps;
    }

    currentPoint = circle->offset;
    tInComponent = 0.0;
}

static Point linearCombination(Point& p1, Point& p2, float t)
{
    Point p;
    p.x = (1.0 - t) * p1.x + t * p2.x;
    p.y = (1.0 - t) * p1.y + t * p2.y;
    return p;
}

const Point* CircleVisitor::next(std::vector<Point>& points)
{
    if(currentPoint + 1 >= circle->offset + circle->pointNumber)
    {
        return nullptr;
    }


    Point &p1 = points[currentPoint];
    Point &p2 = points[currentPoint + 1];
    Point centre = linearCombination(p1, p2, 0.5);
    float r = hypotf(centre.x - p2.x, centre.y - p2.y);
    float offset = atan2f(p1.y - p2.y, p1.x - p2.x);

    p.x = centre.x + r * sinf(offset + tInComponent * 1.5 * 2 * 3.1415);
    p.y = centre.y + r * cosf(offset + tInComponent * 1.5 * 2 * 3.1415);

    tInComponent += deltaT;

    if(tInComponent > 1.0f)
    {
        tInComponent = 0.0;
        currentPoint ++;
    }

    return &p;
}
