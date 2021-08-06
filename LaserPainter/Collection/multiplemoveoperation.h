#ifndef MULTIPLEMOVEOPERATION_H
#define MULTIPLEMOVEOPERATION_H

#include "abstractoperation.h"
#include <set>

class MultipleMoveOperation : public AbstractOperation
{
public:
    MultipleMoveOperation(std::set<Point*> &points, int shiftX, int shiftY);
    virtual ~MultipleMoveOperation();
    void unDo(ShapeCollection &shapeCollection) override;
    void reDo(ShapeCollection &shapeCollection) override;

private:
    void execute();

    int shiftX, shiftY;
    std::set<Point*> points;
};

#endif // MULTIPLEMOVEOPERATION_H
