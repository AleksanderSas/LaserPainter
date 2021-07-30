#include "circlevisitor.h"
#include "math.h"

CircleVisitor::CircleVisitor(unsigned int pointNumber, unsigned int offset)
    : AbstractVisitor(pointNumber, offset, 2)
{}

float CircleVisitor::getComponentDelta(std::vector<Point>& points, unsigned int stepsSize)
{
    int x = points[currentPoint].x - points[currentPoint + 1].x;
    int y = points[currentPoint].y - points[currentPoint + 1].y;
    float r = hypotf(x, y);
    return 1.0f * stepsSize / (3.1415f * 1.25f * r);
}

Point CircleVisitor::compute(std::vector<Point>& points)
{
    Point &p1 = points[currentPoint];
    Point &p2 = points[currentPoint + 1];
    Point centre = linearCombination(p1, p2, 0.5);
    float r = hypotf(centre.x - p2.x, centre.y - p2.y);
    float offset = atan2f(p1.x - p2.x, p1.y - p2.y);

    float angel = offset + tInComponent * 1.5f * 2 * 3.1415f;

    Point p(centre.x + r * sinf(angel), centre.y + r * cosf(angel));
    if(tInComponent > 0.66f)
    {
        tInComponent += deltaT / 2;
    }
    return p;
}
