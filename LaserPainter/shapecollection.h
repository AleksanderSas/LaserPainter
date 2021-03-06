#ifndef SHAPECOLLECTION_H
#define SHAPECOLLECTION_H

#include <vector>
#include "abstractvisitor.h"
#include "shadow.h"
#include <fstream>
#include <utility>

class ShapeCollection
{
public:
    ShapeCollection();
    ~ShapeCollection();
    const Point* next(unsigned int steps);

    void Add(unsigned int x, unsigned int y, ShapeType type, bool enableLaser, int position = -1);
    std::pair<bool, Point*> getOrAddPoint(unsigned int x, unsigned int y, ShapeType type);
    Point* getPoint(unsigned int x, unsigned int y);
    void save(const char* file);
    void load(const char* file);
    void clear();
    std::pair<int, Point> deletePoint(unsigned int x, unsigned int y);
    void insertPointBefore(unsigned int x, unsigned int y, ShapeType type);
    void insertPointBefore(Point &p);

    std::vector<Point> points;
    std::vector<Point>::iterator iter;

private :
    std::vector<Point>::iterator getPointIterator(int x, int y);
    bool SetNextVisitor(bool firstVisitor,  unsigned int steps);
    AbstractVisitor *currectVisitor = nullptr;
    unsigned int currentShape = 0;
    void loadV1(std::ifstream &myfile);
    void loadV2(std::ifstream &myfile);
    void loadV3(std::ifstream &myfile);
};

#endif // SHAPECOLLECTION_H
