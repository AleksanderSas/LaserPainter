#include "beziervisitor.h"
#include <iostream>

BezierVisitor::BezierVisitor(Bezier& bezier, int steps) : bezier(bezier)
{
    if(bezier.curves.size() >= DEGREE)
    {
        int components = (bezier.curves.size() - 1) / (DEGREE - 1);
        deltaT = 1.0 / steps * components;
    }
    else {
          deltaT = 1.0 / steps;
    }
    tmp1 = tmp[0];
    tmp2 = tmp[1];
    currentPoint = 0;
    tInComponent = 0.0;
}

const Point* BezierVisitor::next()
{
    if(tInComponent + deltaT > 1.0)
    {
        tInComponent = 0.0;
        currentPoint += DEGREE - 1;
        if(currentPoint + DEGREE > bezier.curves.size())
        {
            return nullptr;
        }
    }

    compute();
    tInComponent += deltaT;
    return tmp1;
}

static Point line(Point& p1, Point& p2, float t)
{
    Point p;
    p.x = (1.0 - t) * p1.x + t * p2.x;
    p.y = (1.0 - t) * p1.y + t * p2.y;
    return p;
}

void BezierVisitor::compute()
{
    for(int i = DEGREE - 1; i > 0; i--)
    {
        for(int k = 0; k < i; k++)
       {
           tmp1[k] = line(bezier.curves[currentPoint + k], bezier.curves[currentPoint + k+1], tInComponent);
       }
    }

    for(int i = DEGREE - 2; i > 0; i--)
    {
       for(int k = 0; k < i; k++)
       {
           tmp2[k] = line(tmp1[k], tmp1[k+1], tInComponent);
       }
       Point* xxx = tmp1;
       tmp1 = tmp2;
       tmp2 = xxx;
    }
}

