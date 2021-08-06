#ifndef MOVEOPERATION_H
#define MOVEOPERATION_H

#include "abstractoperation.h"

class MoveOperation: public AbstractOperation
{
public:
    MoveOperation(Point &p, float originX, float origing);
    virtual ~MoveOperation() override;
    void unDo(ShapeCollection &shapeCollection) override;
    void reDo(ShapeCollection &shapeCollection) override;

private:
    void execute();

    Point &p;
    float x, y;
};

#endif // MOVEOPERATION_H
