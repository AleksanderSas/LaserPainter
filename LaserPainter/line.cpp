#include "line.h"
#include "linevisitor.h"

Line::Line()
{

}

unsigned int Line::getWeigth()
{
    return pointNumber * 2;
}

AbstractVisitor* Line::getVisitor(unsigned int steps)
{
    return new LineVisitor(this, steps);
}

ShapeType Line::getType()
{
    return ShapeType::LINE;
}
