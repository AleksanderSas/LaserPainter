#include "circle.h"
#include "circlevisitor.h"

Circle::Circle()
{

}

unsigned int Circle::getWeigth()
{
    return pointNumber * 3;
}

AbstractVisitor* Circle::getVisitor(unsigned int steps)
{
    return new CircleVisitor(this, steps);
}

ShapeType Circle::getType()
{
    return ShapeType::CIRCLE;
}
