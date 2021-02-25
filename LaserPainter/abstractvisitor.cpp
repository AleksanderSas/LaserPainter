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
