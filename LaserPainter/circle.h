#ifndef CIRCLE_H
#define CIRCLE_H

#include "abstractshape.h"

class Circle : public AbstractShape
{
public:
    Circle();

    unsigned int getWeigth() override;
    AbstractVisitor* getVisitor(unsigned int steps) override;
    ShapeType getType() override;
};

#endif // CIRCLE_H
