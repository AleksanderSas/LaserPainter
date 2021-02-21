#ifndef BEZIER_H
#define BEZIER_H

#define DEGREE 5

#include <vector>

typedef struct point
{
    int x;
    int y;
} Point;

class Bezier
{
    public:
        Bezier();
        ~Bezier();

        void Add(unsigned int x, unsigned int y);
        Point* getOrAddPoint(unsigned int x, unsigned int y, int squerDist = 1600);
        Point* getPoint(unsigned int x, unsigned int y, int squerDis = 1600);
        void save(const char* file);
        void load(const char* file);
        void clear();
        void deletePoint(unsigned int x, unsigned int y, int squerDis = 1600);

        //friend class BezierVisitor;

        std::vector<Point> curves;
    private:
};

#endif // BEZIER_H
