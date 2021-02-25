#ifndef ABSTRACTVISITOR_H
#define ABSTRACTVISITOR_H

#include "structs.h"
#include <vector>

class AbstractVisitor
{
public:
    AbstractVisitor(unsigned int pointNumber, unsigned int offset);
    virtual ~AbstractVisitor();
    virtual const Point* next(std::vector<Point>& points) = 0;

protected:
    unsigned int pointNumber;
    unsigned int offset;
};

#endif // ABSTRACTVISITOR_H
