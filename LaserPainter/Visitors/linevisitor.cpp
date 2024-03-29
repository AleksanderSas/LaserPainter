#include "linevisitor.h"
#include <math.h>

LineVisitor::LineVisitor(unsigned int pointNumber, unsigned int offset)
    : AbstractVisitor (pointNumber, offset, 2)
{}

float LineVisitor::getComponentDelta(std::vector<Point>& points, unsigned int stepsSize)
{
    float x = points[currentPoint].x - points[currentPoint + 1].x;
    float y = points[currentPoint].y - points[currentPoint + 1].y;
    return 1.0f * stepsSize / hypotf(x, y);
}

Point LineVisitor::compute(std::vector<Point>& points)
{
    return linearCombination(points[currentPoint], points[currentPoint + 1], tInComponent);
}
