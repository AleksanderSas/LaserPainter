#ifndef STRUCTS_H
#define STRUCTS_H

enum ShapeType
{
    BEZIER,
    LINE,
    CIRCLE
};

typedef struct point
{
    int x;
    int y;
    ShapeType type;
    bool enableLaser;
    bool wait;
    point(){}
    point(int x, int y): x(x), y(y) {}
    point(int x, int y, ShapeType t, bool enableLaser, bool wait):
        x(x), y(y), type(t), enableLaser(enableLaser), wait(wait) {}
} Point;

typedef struct pointWithMetadata
{
    Point point;
    bool isNextComponent;
} PointWithMetadata;

#define BEZIER_ "Bezier"
#define LINE_ "Line"
#define CIRCLE_ "Circle"

#endif // STRUCTS_H
