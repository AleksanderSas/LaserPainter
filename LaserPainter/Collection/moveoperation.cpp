#include "moveoperation.h"

MoveOperation::MoveOperation(Point &p, float originX, float originY): p(p), x(originX), y(originY)
{
}

MoveOperation::~MoveOperation() {}

void MoveOperation::execute()
{
    float tmpX = p.x;
    float tmpY = p.y;
    p.x = x;
    p.y = y;
    x = tmpX;
    y = tmpY;
}

void MoveOperation::unDo(ShapeCollection &shapeCollection)
{
    execute();
}

void MoveOperation::reDo(ShapeCollection &shapeCollection)
{
    execute();
}
