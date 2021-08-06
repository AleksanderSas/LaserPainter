#include "multiplemoveoperation.h"

MultipleMoveOperation::MultipleMoveOperation(std::set<Point*> &points, int shiftX, int shiftY): shiftX(shiftX), shiftY(shiftY), points(points)
{
}

MultipleMoveOperation::~MultipleMoveOperation() {}

void MultipleMoveOperation::execute()
{
    for(auto p : points)
    {
        p->x -= shiftX;
        p->y -= shiftY;
    }
    shiftX *= -1;
    shiftY *= -1;
}

void MultipleMoveOperation::unDo(ShapeCollection &shapeCollection)
{
    execute();
}

void MultipleMoveOperation::reDo(ShapeCollection &shapeCollection)
{
    execute();
}
