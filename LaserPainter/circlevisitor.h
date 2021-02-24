#ifndef CIRCLEVISITOR_H
#define CIRCLEVISITOR_H

#include "abstractvisitor.h"
#include "circle.h"

class CircleVisitor : public AbstractVisitor
{
public:
    CircleVisitor(Circle* circle, unsigned int steps);
    const Point* next(std::vector<Point>& points) override;

private:
    Circle* circle;
    unsigned int currentPoint;
    float deltaT;
    float tInComponent;
    Point centre;
    unsigned int r;
    point p;
};

#endif // CIRCLEVISITOR_H
