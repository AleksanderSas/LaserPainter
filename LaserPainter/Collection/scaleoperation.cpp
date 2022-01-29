#include "scaleoperation.h"

ScaleOperation::ScaleOperation(std::set<Point*> &points, std::vector<Point> &originalPoints)
    : points(points), originalPoints(originalPoints)
{
}

ScaleOperation::~ScaleOperation() {}

void ScaleOperation::execute()
{
    auto original = originalPoints.begin();
    for(Point* p : points)
    {
        Point& originalVal = *original;

        float newX = p->x;
        p->x = originalVal.x;
        originalVal.x = newX;

        float newY = p->y;
        p->y = originalVal.y;
        originalVal.y = newY;

        original++;
    }
}

void ScaleOperation::unDo(ShapeCollection &shapeCollection)
{
    execute();
}

void ScaleOperation::reDo(ShapeCollection &shapeCollection)
{
    execute();
}
