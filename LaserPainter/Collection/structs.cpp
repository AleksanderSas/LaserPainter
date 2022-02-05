#include "structs.h"

std::string getShapeName(ShapeType type)
{
    switch(type)
    {
        case ShapeType::BEZIER: return BEZIER_;
        case ShapeType::LINE: return LINE_;
        case ShapeType::HALF_CIRCLE: return HALF_CIRCLE_;
        case ShapeType::CIRCLE: return CIRCLE_;
    }
}
