#include "mathutils.h"
#include "math.h"

int MathUtils::squareDist(std::pair<int,int> &p1, std::pair<int,int> &p2)
{
    int dx = p1.first - p2.first;
    int dy = p1.second - p2.second;
    return dx * dx + dy * dy;
}

std::pair<float, float> MathUtils::getNormalizedVector(std::pair<int,int> &start, std::pair<int,int> &end)
{
    std::pair<float, float> vec = getNormalizedOrtogonal(start, end);
    return std::pair<float, float>(-vec.second, vec.first);
}

std::pair<float, float> MathUtils::getNormalizedOrtogonal(std::pair<int,int> &start, std::pair<int,int> &end)
{
    int dx = end.first - start.first;
    int dy = end.second - start.second;
    if(dx == 0) return std::pair<float, float>(1.0, 0.0);
    if(dy == 0) return std::pair<float, float>(0.0, 1.0);
    float b = dx > 0? 1.0f : -1.0f;
    float a = -b * dy / dx;
    float len = hypotf(1.0, a);
    return std::pair<float, float>(a / len, b / len);
}
