#ifndef LINE_H
#define LINE_H

#include "abstractshape.h"

class Line : public AbstractShape
{
public:
    Line();

    unsigned int getWeigth() override;
    AbstractVisitor* getVisitor(unsigned int steps) override;
    ShapeType getType() override;

};

#endif // LINE_H
