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

    void Add(unsigned int x, unsigned int y, ShapeType type, bool enableLaser, bool wait, int position = -1);
    std::pair<bool, Point*> getOrAddPoint(unsigned int x, unsigned int y, ShapeType type);
    Point* getPoint(unsigned int x, unsigned int y);
    void clear();
    std::pair<int, Point> deletePoint(unsigned int x, unsigned int y);
    void insertPointAfter(Point &p);

    std::vector<Point> points;
    std::vector<Point>::iterator iter;

private :
    std::vector<Point>::iterator getPointIterator(int x, int y);
    bool SetNextVisitor(bool firstVisitor);
    AbstractVisitor *currentVisitor = nullptr;
    unsigned int currentShape = 0;
    std::vector<Point>::iterator insertPosition;
};

#endif // SHAPECOLLECTION_H
