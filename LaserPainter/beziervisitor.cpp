#include "beziervisitor.h"
#include <iostream>
#include <math.h>
BezierVisitor::BezierVisitor(unsigned int pointNumber, unsigned int offset)
    : AbstractVisitor (pointNumber, offset, DEGREE)
{
    deltaT = -1.0f;
    tmp1 = tmp[0];
    tmp2 = tmp[1];
    currentPoint = offset;
    tInComponent = 0.0;
}

float BezierVisitor::getComponentDelta(std::vector<Point>& points, unsigned int stepsSize)
{
    if(points.size() < currentPoint + DEGREE)
    {
        return 1.0f;
    }
    float sum = 0.0f;
    Point previous = compute(points, 0.0f);
    float t = 0.05;
    while(t < 1.0f)
    {
        Point tmp = compute(points, t);
        t += 0.05f;
        sum += hypot(previous.x - tmp.x, previous.y - tmp.y);
        previous = tmp;
    }
    return 1.0f * stepsSize / sum;
}

Point BezierVisitor::compute(std::vector<Point> &points, float t)
{
    for(unsigned int i = DEGREE - 1; i > 0; i--)
    {
        for(unsigned int k = 0; k < i; k++)
       {
           tmp1[k] = linearCombination(points[currentPoint + k], points[currentPoint + k+1], t);
       }
    }

    for(int i = DEGREE - 2; i > 0; i--)
    {
       for(int k = 0; k < i; k++)
       {
           tmp2[k] = linearCombination(tmp1[k], tmp1[k+1], t);
       }
       Point* xxx = tmp1;
       tmp1 = tmp2;
       tmp2 = xxx;
    }
    return tmp1[0];
}

Point BezierVisitor::compute(std::vector<Point> &points)
{
    return compute(points, tInComponent);
}

