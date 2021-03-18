#include "circlevisitor.h"
#include "math.h"

CircleVisitor::CircleVisitor(unsigned int pointNumber, unsigned int offset, unsigned int steps) : AbstractVisitor(pointNumber, offset)
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

const Point* CircleVisitor::next(std::vector<Point>& points)
{
    if(currentPoint + 1 >= offset + pointNumber)
    {
        return nullptr;
    }


    Point &p1 = points[currentPoint];
    Point &p2 = points[currentPoint + 1];
    Point centre = linearCombination(p1, p2, 0.5);
    float r = hypotf(centre.x - p2.x, centre.y - p2.y);
    float offset = atan2f(p1.x - p2.x, p1.y - p2.y);

    float angel = offset + tInComponent * 1.5f * 2 * 3.1415f;

    p.x = centre.x + r * sinf(angel);
    p.y = centre.y + r * cosf(angel);
    p.enableLaser = p1.enableLaser;

    tInComponent += deltaT;
    if(tInComponent > 0.66f)
    {
        tInComponent += deltaT / 2;
    }

    if(tInComponent > 1.0f)
    {
        tInComponent = 0.0;
        currentPoint ++;
    }

    return &p;
}
