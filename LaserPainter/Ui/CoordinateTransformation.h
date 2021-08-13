#ifndef COORDINATETRANSFORMATION_H
#define COORDINATETRANSFORMATION_H

#include <tuple>
#include "../Collection/structs.h"

std::pair<int,int> scaleToCollection(int x, int y);
std::pair<int,int> toCollectionPoint2(int x, int y);
std::pair<int,int> fromCollectionPoint(const Point &p);

#endif // COORDINATETRANSFORMATION_H
