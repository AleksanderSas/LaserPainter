#ifndef MOVEOPERATION_H
#define MOVEOPERATION_H

#include "abstractoperation.h"

class MoveOperation: public AbstractOperation
{
public:
    MoveOperation(Point &p, int originX, int origing);
    virtual ~MoveOperation();
    void unDo(ShapeCollection &shapeCollection) override;
    void reDo(ShapeCollection &shapeCollection) override;

private:
    void execute();

    int x, y;
    Point &p;
};

#endif // MOVEOPERATION_H
