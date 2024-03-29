#ifndef SHAPECOLLECTION_H
#define SHAPECOLLECTION_H

#include <vector>
#include "Visitors/abstractvisitor.h"
#include "shadow.h"
#include <fstream>
#include <utility>

struct SelectedPoint
{
    SelectedPoint(bool isAdded, int idx, Point* point);
    bool isAdded;
    int idx;
    Point* point;
};

struct ComponentPoints
{
    ComponentPoints(int prev,int current, int end);
    int previousComponentStartIdx;
    int currentComponentStartIdx;
    int currentComponentEndIdx;
};

class ShapeCollection
{
public:
    ShapeCollection();
    ~ShapeCollection();
    const PointWithMetadata* next(unsigned int stepsSize, int curvatureLevel);
    void restart();

    void Add(float x, float y, ShapeType type, bool enableLaser, bool wait, int position = -1);
    SelectedPoint getOrAddPoint(int x, int y, ShapeType type);
    Point* getPoint(int x, int y);
    void clear();
    std::pair<int, Point> deletePoint(int x, int y);
    void insertPointAfter(Point &p);

    ComponentPoints getPointsFromComponent(unsigned int idx);

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
    Point previousPoint, previousPreviousPoint;
};

#endif // SHAPECOLLECTION_H
