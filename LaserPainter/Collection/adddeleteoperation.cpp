#include "adddeleteoperation.h"

AddDeleteOperation::AddDeleteOperation(Point p, int position): position(position), p(p)
{
    addOnUndo = true;
}

AddDeleteOperation::AddDeleteOperation(Point p): p(p)
{
    addOnUndo = false;
}

AddDeleteOperation::~AddDeleteOperation() {}

void AddDeleteOperation::execute(ShapeCollection &shapeCollection, bool add)
{
    if(add)
    {
        shapeCollection.Add(p.x, p.y, p.type, p.enableLaser, position);
    }
    else
    {
        position = shapeCollection.deletePoint(p.x, p.y).first;
    }
}

void AddDeleteOperation::unDo(ShapeCollection &shapeCollection)
{
    execute(shapeCollection, addOnUndo);
}

void AddDeleteOperation::reDo(ShapeCollection &shapeCollection)
{
    execute(shapeCollection, !addOnUndo);
}
