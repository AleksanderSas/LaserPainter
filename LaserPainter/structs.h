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
} Point;

#define BEZIER_ "Bezier"
#define LINE_ "Line"
#define CIRCLE_ "Circle"

#endif // STRUCTS_H
