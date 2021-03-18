#include "beziervisitor.h"
#include <iostream>

BezierVisitor::BezierVisitor(unsigned int pointNumber, unsigned int offset, unsigned int steps) : AbstractVisitor (pointNumber, offset)
{
    if(pointNumber >= DEGREE)
    {
        int components = (pointNumber - 1) / (DEGREE - 1);
        deltaT = 1.0f / steps * components;
    }
    else {
          deltaT = 1.0f / steps;
    }
    tmp1 = tmp[0];
    tmp2 = tmp[1];
    currentPoint = offset;
    tInComponent = 0.0;
}

const Point* BezierVisitor::next(std::vector<Point>& points)
{
    if(currentPoint + DEGREE > offset + pointNumber)
    {
        return nullptr;
    }

    compute(points);
    tmp1->enableLaser = points[currentPoint].enableLaser;
    tInComponent += deltaT;

    if(tInComponent + deltaT > 1.0f)
    {
        tInComponent = 0.0;
        currentPoint += DEGREE - 1;
    }

    return tmp1;
}

void BezierVisitor::compute(std::vector<Point> &points)
{
    for(unsigned int i = DEGREE - 1; i > 0; i--)
    {
        for(unsigned int k = 0; k < i; k++)
       {
           tmp1[k] = linearCombination(points[currentPoint + k], points[currentPoint + k+1], tInComponent);
       }
    }

    for(int i = DEGREE - 2; i > 0; i--)
    {
       for(int k = 0; k < i; k++)
       {
           tmp2[k] = linearCombination(tmp1[k], tmp1[k+1], tInComponent);
       }
       Point* xxx = tmp1;
       tmp1 = tmp2;
       tmp2 = xxx;
    }
}

