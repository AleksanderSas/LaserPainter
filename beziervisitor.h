#ifndef BEZIERVISITOR_H
#define BEZIERVISITOR_H

#include <vector>
#include "bezier.h"

class BezierVisitor
{
    public:
        BezierVisitor(Bezier& bezier, int steps);
        const Point* next();

    private:
        Bezier& bezier;

        float tInComponent;
        float deltaT;
        unsigned int currentPoint;
        Point tmp[2][DEGREE];
        Point* tmp1;
        Point* tmp2;
        int _dummy_;

        void compute();
};
#endif // BEZIERVISITOR_H
