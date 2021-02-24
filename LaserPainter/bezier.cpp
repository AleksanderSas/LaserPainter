#include "bezier.h"
#include "math.h"
#include <iostream>
#include <fstream>
#include "beziervisitor.h"

Bezier::Bezier() : AbstractShape()
{
}

unsigned int Bezier::getWeigth()
{
    return pointNumber;
}

AbstractVisitor* Bezier::getVisitor(unsigned int steps)
{
    return new BezierVisitor(this, steps);
}

ShapeType Bezier::getType()
{
    return ShapeType::BEZIER;
}





