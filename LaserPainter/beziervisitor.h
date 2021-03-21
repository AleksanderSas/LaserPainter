#ifndef BEZIERVISITOR_H
#define BEZIERVISITOR_H

#include "abstractvisitor.h"

#define DEGREE 5

class BezierVisitor : public AbstractVisitor
{
    public:
        BezierVisitor(unsigned int pointNumber, unsigned int offset);

    private:
        Point compute(std::vector<Point>& points) override;
        Point compute(std::vector<Point>& points, float t);
        float getComponentDelta(std::vector<Point>& points, unsigned int stepsSize) override;
        Point tmp[2][DEGREE];
        Point* tmp1;
        Point* tmp2;
};
#endif // BEZIERVISITOR_H
