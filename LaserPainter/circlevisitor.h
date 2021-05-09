#ifndef CIRCLEVISITOR_H
#define CIRCLEVISITOR_H

#include "abstractvisitor.h"

class CircleVisitor : public AbstractVisitor
{
public:
    CircleVisitor(unsigned int pointNumber, unsigned int offset);

private:
    Point compute(std::vector<Point>& points) override;
    float getComponentDelta(std::vector<Point>& points, unsigned int stepsSize) override;
    Point centre;
    point p;
};

#endif // CIRCLEVISITOR_H
