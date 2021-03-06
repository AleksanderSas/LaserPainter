#ifndef ADDOPERATION_H
#define ADDOPERATION_H
#include "abstractoperation.h"
#include "structs.h"

class AddDeleteOperation: public AbstractOperation
{
public:
    AddDeleteOperation(Point p, int position);
    AddDeleteOperation(Point p);
    virtual ~AddDeleteOperation();
    void unDo(ShapeCollection &shapeCollection) override;
    void reDo(ShapeCollection &shapeCollection) override;

private:
    void execute(ShapeCollection &shapeCollection, bool add);

    int position;
    Point p;
    bool addOnUndo;
};

#endif // ADDOPERATION_H
