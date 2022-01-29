#ifndef SCALEOPERATION_H
#define SCALEOPERATION_H

#include "abstractoperation.h"
#include <set>

using namespace std;

class ScaleOperation: public AbstractOperation
{
public:
    ScaleOperation(std::set<Point*> &points, std::vector<Point> &originalPoints);
    virtual ~ScaleOperation() override;
    void unDo(ShapeCollection &shapeCollection) override;
    void reDo(ShapeCollection &shapeCollection) override;

private:
    std::set<Point*> points;
    std::vector<Point> originalPoints;
    void execute();
};

#endif // SCALEOPERATION_H
