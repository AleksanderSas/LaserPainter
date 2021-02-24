#ifndef LINEVISITOR_H
#define LINEVISITOR_H

#include "abstractvisitor.h"
#include "line.h"

class LineVisitor : public AbstractVisitor
{
public:
    LineVisitor(Line* bezier, int steps);
    const Point* next(std::vector<Point>& points) override;

private:
    Line *line;
    unsigned int currentPoint;
    float deltaT;
    float tInComponent;
    point p;
};

#endif // LINEVISITOR_H
