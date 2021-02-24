#ifndef SHAPECOLLECTION_H
#define SHAPECOLLECTION_H

#include "abstractshape.h"
#include <vector>
#include "abstractvisitor.h"
#include "shadow.h"
#include <fstream>

class ShapeCollection
{
public:
    ShapeCollection();
    ~ShapeCollection();
    const Point* next(unsigned int steps);

    void Add(unsigned int x, unsigned int y, ShapeType type);
    Point* getOrAddPoint(unsigned int x, unsigned int y, ShapeType type, unsigned int squerDist = 1600);
    Point* getPoint(unsigned int x, unsigned int y, unsigned int squerDis = 1600);
    void save(const char* file);
    void load(const char* file);
    void clear();
    void deletePoint(unsigned int x, unsigned int y, unsigned int squerDis = 1600);
    unsigned int getTotalWeigth();

    std::vector<Point> points;

private :
    std::vector<AbstractShape*> shapes;
    AbstractVisitor *currectVisitor = nullptr;
    unsigned int currentShape = 0;
    void loadV1(std::ifstream &myfile);
    void loadV2(std::ifstream &myfile);
};

#endif // SHAPECOLLECTION_H
