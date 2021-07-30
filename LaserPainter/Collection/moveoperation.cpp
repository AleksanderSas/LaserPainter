#include "moveoperation.h"

MoveOperation::MoveOperation(Point &p, int originX, int originY): p(p), x(originX), y(originY)
{
}

MoveOperation::~MoveOperation() {}

void MoveOperation::execute()
{
    int tmpX = p.x;
    int tmpY = p.y;
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
