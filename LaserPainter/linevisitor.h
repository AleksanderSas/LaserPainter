#ifndef LINEVISITOR_H
#define LINEVISITOR_H

#include "abstractvisitor.h"

class LineVisitor : public AbstractVisitor
{
public:
    LineVisitor(unsigned int pointNumber, unsigned int offset, unsigned int steps);
    const Point* next(std::vector<Point>& points) override;

private:
    unsigned int currentPoint;
    float deltaT;
    float tInComponent;
    point p;
};

#endif // LINEVISITOR_H
