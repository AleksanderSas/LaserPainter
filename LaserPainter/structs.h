#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct point
{
    int x;
    int y;
} Point;

enum ShapeType
{
    BEZIER,
    LINE,
    CIRCLE
};

#define BEZIER_ "Bezier"
#define LINE_ "Line"
#define CIRCLE_ "Circle"

#endif // STRUCTS_H
