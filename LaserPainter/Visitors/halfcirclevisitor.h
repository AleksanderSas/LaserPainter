#ifndef HALFCIRCLEVISITOR_H
#define HALFCIRCLEVISITOR_H

#include "abstractvisitor.h"

class HalfCircleVisitor : public AbstractVisitor
{
public:
    HalfCircleVisitor(unsigned int pointNumber, unsigned int offset);

private:
    Point compute(std::vector<Point>& points) override;
    float getComponentDelta(std::vector<Point>& points, unsigned int stepsSize) override;
    void computeCentre(std::vector<Point>& points);
    float x, y, r, beginAngel, fraction = 1.0f;
    int direction = 1;
};

#endif // HALFCIRCLEVISITOR_H
