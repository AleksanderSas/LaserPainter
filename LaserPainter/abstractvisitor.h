#ifndef ABSTRACTVISITOR_H
#define ABSTRACTVISITOR_H

#include "structs.h"
#include <vector>

class AbstractVisitor
{
public:
    AbstractVisitor(unsigned int pointNumber, unsigned int offset, unsigned int pointsPerComponent);
    virtual ~AbstractVisitor();
    const PointWithMetadata* next(std::vector<Point>& points, unsigned int stepsSizet);

protected:
    virtual Point compute(std::vector<Point>& points) = 0;
    virtual float getComponentDelta(std::vector<Point>& points, unsigned int stepsSize) = 0;
    unsigned int pointNumber;
    unsigned int offset;
    PointWithMetadata p;
    float tInComponent;
    float deltaT;
    unsigned int currentPoint;
    unsigned int pointsPerComponent;
};

Point linearCombination(Point& p1, Point& p2, float t);

#endif // ABSTRACTVISITOR_H
