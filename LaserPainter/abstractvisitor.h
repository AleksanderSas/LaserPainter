#ifndef ABSTRACTVISITOR_H
#define ABSTRACTVISITOR_H

#include "structs.h"
#include <vector>

class AbstractVisitor
{
public:
    AbstractVisitor();
    virtual ~AbstractVisitor();
    virtual const Point* next(std::vector<Point>& points) = 0;
};

#endif // ABSTRACTVISITOR_H
