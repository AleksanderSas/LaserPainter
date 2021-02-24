#ifndef ABSTRACTSHAPE_H
#define ABSTRACTSHAPE_H

#include "abstractvisitor.h"

class AbstractShape
{
public:
    AbstractShape();
    virtual ~AbstractShape();
    virtual unsigned int getWeigth() = 0;
    virtual AbstractVisitor* getVisitor(unsigned int steps) = 0;
    virtual ShapeType getType() = 0;

    unsigned int pointNumber;
    unsigned int offset;
};

#endif // ABSTRACTSHAPE_H
