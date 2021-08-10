#include "CoordinateTransformation.h"

std::pair<int,int> toCollectionPoint2(int x, int y)
{
    return std::pair<int,int>(x * 4, (y + 1024 - 780) * 4); // move by 244
}

std::pair<int,int> fromCollectionPoint(const Point &p)
{
    return std::pair<int,int>(p.x / 4, p.y / 4 - 244);
}

std::pair<int,int> scaleToCollection(int x, int y)
{
    return std::pair<int,int>(x * 4, y * 4);
}
