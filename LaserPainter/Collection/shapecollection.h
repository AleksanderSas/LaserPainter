#ifndef SHAPECOLLECTION_H
#define SHAPECOLLECTION_H

#include <vector>
#include "Visitors/abstractvisitor.h"
#include "shadow.h"
#include <fstream>
#include <utility>

class ShapeCollection
{
public:
    ShapeCollection();
    ~ShapeCollection();
    const PointWithMetadata* next(unsigned int stepsSize);
    void restart();

    void Add(float x, float y, ShapeType type, bool enableLaser, bool wait, int position = -1);
    std::pair<bool, Point*> getOrAddPoint(int x, int y, ShapeType type);
    Point* getPoint(int x, int y);
    void clear();
    std::pair<int, Point> deletePoint(int x, int y);
    void insertPointAfter(Point &p);

    //<start point index, end point index>
    std::pair<unsigned int, unsigned int> getPointsFromComponent(unsigned int idx);

    //return idx of last point from invalid component. If collection is valie, -1
    int validate();

    std::vector<Point> points;
    std::vector<Point>::iterator iter;

private :
    std::vector<Point>::iterator getPointIterator(float x, float y);
    bool SetNextVisitor(bool firstVisitor);
    AbstractVisitor *currentVisitor = nullptr;
    unsigned int currentShape = 0;
    std::vector<Point>::iterator insertPosition;
};

#endif // SHAPECOLLECTION_H
