#include "abstractvisitor.h"
#include "shapecollection.h"

AbstractVisitor::AbstractVisitor(unsigned int pointNumber, unsigned int offset) :
    pointNumber(pointNumber),
    offset(offset)
{
}

AbstractVisitor::~AbstractVisitor()
{
}

Point linearCombination(Point& p1, Point& p2, float t)
{
    Point p;
    p.x = (1.0 - t) * p1.x + t * p2.x;
    p.y = (1.0 - t) * p1.y + t * p2.y;
    return p;
}
