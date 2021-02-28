#ifndef BEZIERVISITOR_H
#define BEZIERVISITOR_H

#include "abstractvisitor.h"

#define DEGREE 5

class BezierVisitor : public AbstractVisitor
{
    public:
        BezierVisitor(unsigned int pointNumber, unsigned int offset, unsigned int steps);
        const Point* next(std::vector<Point>& points) override;

    private:
        float tInComponent;
        float deltaT;
        unsigned int currentPoint;
        Point tmp[2][DEGREE];
        Point* tmp1;
        Point* tmp2;
        int _dummy_;

        void compute(std::vector<Point>& points);
};
#endif // BEZIERVISITOR_H
