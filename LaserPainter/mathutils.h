#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <bits/stl_pair.h>

class MathUtils
{
public:
    static int squareDist(std::pair<int,int> &p1, std::pair<int,int> &p2);
    static std::pair<float, float> getNormalizedVector(std::pair<int,int> &start, std::pair<int,int> &end);
    static std::pair<float, float> getNormalizedOrtogonal(std::pair<int,int> &start, std::pair<int,int> &end);
};

#endif // MATHUTILS_H
