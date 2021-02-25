#ifndef CIRCLEVISITOR_H
#define CIRCLEVISITOR_H

#include "abstractvisitor.h"

class CircleVisitor : public AbstractVisitor
{
public:
    CircleVisitor(unsigned int pointNumber, unsigned int offset, unsigned int steps);
    const Point* next(std::vector<Point>& points) override;

private:
    unsigned int currentPoint;
    float deltaT;
    float tInComponent;
    Point centre;
    unsigned int r;
    point p;
};

#endif // CIRCLEVISITOR_H
