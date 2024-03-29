#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>

enum ShapeType
{
    BEZIER,
    LINE,
    CIRCLE,
    HALF_CIRCLE
};

typedef struct point
{
    float x;
    float y;
    ShapeType type;
    bool enableLaser;
    bool wait;
    point(){}
    point(float x, float y): x(x), y(y) {}
    point(float x, float y, ShapeType t, bool enableLaser, bool wait):
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
#define HALF_CIRCLE_ "Half Circle"

std::string getShapeName(ShapeType type);

#endif // STRUCTS_H
