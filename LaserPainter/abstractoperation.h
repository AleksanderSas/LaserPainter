#ifndef ABSTRACTOPERATION_H
#define ABSTRACTOPERATION_H
#include "shapecollection.h"

enum OperationType
{
    MOVE,
    ADD,
    REMOVE
};

class AbstractOperation
{
public:
    virtual void unDo(ShapeCollection &shapeCollection) = 0;
    virtual void reDo(ShapeCollection &shapeCollection) = 0;
};

#endif // ABSTRACTOPERATION_H
