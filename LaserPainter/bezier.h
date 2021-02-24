#ifndef BEZIER_H
#define BEZIER_H

#define DEGREE 5

#include <vector>
#include "abstractshape.h"
#include "structs.h"

class Bezier : public AbstractShape
{
    public:
        Bezier();

        unsigned int getWeigth() override;
        AbstractVisitor* getVisitor(unsigned int steps) override;
        ShapeType getType() override;
};

#endif // BEZIER_H
