#ifndef LINEVISITOR_H
#define LINEVISITOR_H

#include "abstractvisitor.h"

class LineVisitor : public AbstractVisitor
{
public:
    LineVisitor(unsigned int pointNumber, unsigned int offset);

private:
    Point compute(std::vector<Point>& points) override;
    float getComponentDelta(std::vector<Point>& points, unsigned int stepsSize) override;
    point p;
};

#endif // LINEVISITOR_H
