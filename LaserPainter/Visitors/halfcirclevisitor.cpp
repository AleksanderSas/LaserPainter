#include "halfcirclevisitor.h"
#include "math.h"

HalfCircleVisitor::HalfCircleVisitor(unsigned int pointNumber, unsigned int offset)
    : AbstractVisitor (pointNumber, offset, 3)
{}

float inline numeratorX(Point &p1, Point &p2, Point &p3)
{
    return p2.x * p2.x  * p3.y + p2.y * p2.y * p3.y - p1.x * p1.x * p3.y - p1.y * p1.y * p3.y;
}

float inline numeratorY(Point &p1, Point &p2, Point &p3)
{
    return p1.x * p1.x * p3.x + p1.y * p1.y * p3.x - p2.x * p2.x * p3.x - p2.y * p2.y * p3.x;
}

float inline denominator(Point &p1, Point &p2, Point &p3)
{
    return p1.y * p3.x - p1.y * p2.x + p2.y * p1.x - p2.y * p3.x + p3.y * p2.x - p3.y * p1.x;
}


void HalfCircleVisitor::computeCentre(std::vector<Point>& points)
{
    Point &p1 = points[currentPoint];
    Point &p2 = points[currentPoint + 1];
    Point &p3 = points[currentPoint + 2];

    float den = denominator(p1, p2, p3);
    if(abs(den) < 0.05f) den = den < 0.0f? -0.05f : 0.05f;
    x = 0.5f * (numeratorX(p1, p2, p3) + numeratorX(p3, p1, p2) + numeratorX(p2, p3, p1)) / den;
    y = 0.5f * (numeratorY(p1, p2, p3) + numeratorY(p3, p1, p2) + numeratorY(p2, p3, p1)) / den;
    r = hypotf(p1.x - x, p1.y - y);

    beginAngel = atan2f(p1.x - x, p1.y - y);
    float endAngel = atan2f(p3.x - x, p3.y - y);

    float ap2Angel = atan2f(p2.x - x, p2.y - y);
    if((beginAngel <= ap2Angel && ap2Angel <= endAngel) || (beginAngel >= ap2Angel && ap2Angel >= endAngel))
    {
        fraction = abs(endAngel - beginAngel) / (2.0f * M_PIf32);
        direction = beginAngel > endAngel? -1 : 1;
    }
    else
    {
        fraction = (2.0f * M_PIf32 - abs(endAngel - beginAngel)) / (2.0f * M_PIf32);
        direction = beginAngel > endAngel? 1 : -1;
    }

}

float HalfCircleVisitor::getComponentDelta(std::vector<Point>& points, unsigned int stepsSize)
{
    computeCentre(points);

    return 1.0f * stepsSize / (M_PIf32* r * 2.0f * fraction);
}

Point HalfCircleVisitor::compute(std::vector<Point>& points)
{
    float angel = beginAngel + tInComponent * 2.0f * M_PIf32 * fraction * direction;

    Point p(x + r * sinf(angel), y + r * cosf(angel));
    return p;
}
