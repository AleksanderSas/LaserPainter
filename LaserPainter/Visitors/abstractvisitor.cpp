#include "abstractvisitor.h"
#include "Collection/shapecollection.h"
#include "math.h"

AbstractVisitor::AbstractVisitor(unsigned int pointNumber, unsigned int offset, unsigned int pointsPerComponent) :
    pointNumber(pointNumber),
    offset(offset),
    tInComponent(0.0f),
    deltaT(-1.0f),
    currentPoint(offset),
    pointsPerComponent(pointsPerComponent)
{
}

AbstractVisitor::~AbstractVisitor()
{
}

unsigned int AbstractVisitor::getPointPerComponent()
{
    return pointsPerComponent;
}

Point linearCombination(Point& p1, Point& p2, float t)
{
    Point p;
    p.x = (1.0f - t) * p1.x + t * p2.x;
    p.y = (1.0f - t) * p1.y + t * p2.y;
    return p;
}

static float computeCurvature(Point current, Point previous, Point previousPrevious)
{
    float dx = current.x - previous.x;
    float dy = current.y - previous.y;
    float ddx =  dx - previous.x + previousPrevious.x;
    float ddy =  dy - previous.y + previousPrevious.y;

    float nominator = abs(dx*ddy - dy*ddx);
    float denominator = hypot(dx, dy);
    denominator = denominator * denominator * denominator;
    float curvature = denominator > 0? nominator / denominator : 0.0;

    return curvature;
}

//recomended curvatureLevel range 0-10
static float getDeltaT(float curv, float deltaT, int curvatureLevel)
{
    const int max = 10;
    float modifyerTreshold = deltaT * curvatureLevel / max / 2;
    float curvatureModifier = curv * curvatureLevel * 2;
    return modifyerTreshold > curvatureModifier
           ?deltaT - curvatureModifier
           :deltaT - modifyerTreshold;
}

//nullpth is returned when whole sequence is visited
const PointWithMetadata* AbstractVisitor::next(std::vector<Point>& points, unsigned int stepsSize, Point prev, Point prevPrev, int curvatureLevel)
{
    if(currentPoint + pointsPerComponent - 1 >= offset + pointNumber)
    {
        return nullptr;
    }
    if(deltaT < 0)
    {
        deltaT = getComponentDelta(points, stepsSize);
    }

    p.isNextComponent = tInComponent == 0.0f;

    if(tInComponent > 1.0f)
    {
        tInComponent = 1.0f;
        p.point = compute(points);
        tInComponent = 0.0;
        currentPoint += pointsPerComponent - 1;
        deltaT = getComponentDelta(points, stepsSize);
    }
    else {
        p.point = compute(points);
        tInComponent += deltaT;
        if(!p.point.enableLaser)
        {
            tInComponent += deltaT;
        }
    }
    float curv = computeCurvature(p.point, prev, prevPrev);
    float newT =  getDeltaT(curv, deltaT, curvatureLevel);
    newT = newT / deltaT;
    printf("curv: %f delta %f dif: %f\n", curv ,deltaT, newT);
    p.point.enableLaser = points[currentPoint].enableLaser;
    p.isNextComponent &= points[currentPoint].wait;
    return &p;
}
