#include "project.h"
#include "shapecollection.h"
#include <string>
#include <math.h>

Project::Project()
{
}

Project::~Project()
{
    clear();
}

void Project::clear()
{
    shape.clear();
    move.clear();
}
bool Project::isEmpty()
{
    return shape.points.size() > 0 || move.points.size() > 0;
}

void Project::loadV2(std::ifstream &myfile)
{
    while(myfile.good())
    {
        unsigned int x, y, lineType;
        myfile >> lineType;
        myfile >> x;
        myfile >> y;
        shape.Add(x, y, (ShapeType)lineType, true, false);
    }
}

void Project::loadV3(std::ifstream &myfile)
{
    while(myfile.good())
    {
        unsigned int x, y, lineType;
        bool enableLaser;
        myfile >> lineType;
        myfile >> x;
        myfile >> y;
        myfile >> enableLaser;
        shape.Add(x, y, (ShapeType)lineType, enableLaser, false);
    }
}

void Project::loadV4(std::ifstream &myfile)
{
    while(myfile.good())
    {
        unsigned int x, y, lineType;
        bool enableLaser, wait;
        myfile >> lineType;
        myfile >> x;
        myfile >> y;
        myfile >> enableLaser;
        myfile >> wait;
        shape.Add(x, y, (ShapeType)lineType, enableLaser, wait);
    }
}

void Project::readPointSequenceV5(std::ifstream &myfile, ShapeCollection& sc)
{
    int pointNumber = 0;
    myfile >> pointNumber;
    for(int i = 0; i < pointNumber; i++)
    {
        if(!myfile.good())
        {
            std::string errorMessage = "Expected ";
            errorMessage+= pointNumber +  " points, butfound only " + i;
            throw errorMessage;
        }

        unsigned int x, y, lineType;
        bool enableLaser, wait;
        myfile >> lineType;
        myfile >> x;
        myfile >> y;
        myfile >> enableLaser;
        myfile >> wait;
        sc.Add(x, y, (ShapeType)lineType, enableLaser, wait);
    }
}

void Project::loadV5(std::ifstream &myfile)
{
    myfile >> moveScale;
    readPointSequenceV5(myfile, shape);
    readPointSequenceV5(myfile, move);
}

void Project::load(std::string &file)
{
    std::ifstream myfile;
    myfile.open(file);
    try
    {
        std::string version;
        myfile >> version;
        if(version != "V5" && version != "V4" && version != "V2" && version != "V3")
        {
            throw "only V2, V3, V4 and V5 standards are supported";
        }

        if(version == "V2")
            loadV2(myfile);
        if(version == "V3")
            loadV3(myfile);
        if(version == "V3")
            loadV3(myfile);
        if(version == "V4")
            loadV4(myfile);
        if(version == "V5")
            loadV5(myfile);
    }catch(std::string error)
    {
        myfile.close();
        clear();
        throw error;
    }
}

void Project::save(const char* file)
{
    std::ofstream myfile;
    myfile.open (file);
    myfile << "V5" << std::endl;
    myfile << moveScale << std::endl;
    myfile << shape.points.size() << std::endl;
    for(Point &p : shape.points)
    {
        myfile << p.type << " " << p.x << " " << p.y << " " << p.enableLaser << " " << p.wait << std::endl;
    }

    myfile << std::endl << move.points.size() << std::endl;
    for(Point &p : move.points)
    {
        myfile << p.type << " " << p.x << " " << p.y << " " << p.enableLaser << " " << p.wait << std::endl;
    }
    myfile.close();
}

void Project::restart()
{
    move.restart();
    shape.restart();
    path = nullptr;
    rotateSin = 0.0f;
    rotateCos = 1.0f;
}

void Project::SetNextPath(unsigned int moveSpeed,int curvatureLevel)
{
    if(move.points.size() > 0)
    {
        path = move.next(moveSpeed, curvatureLevel);
        while(path == nullptr)
        {
            path = move.next(moveSpeed, curvatureLevel);
        }
    }
}

static float respectRange(float value)
{
    value = value < 0.0f? 0.0f : value;
    return value > 4095.0f? 4095.0f : value;
}

Point rotateScaleAndShift(const Point& p, float sin, float cos, const Point& offset, int scale)
{
    float xTmp = p.x - 2048;
    float yTmp = p.y - 2048;
    if(scale != 100)
    {
        xTmp = xTmp * scale / 100;
        yTmp = yTmp * scale / 100;
    }
    float x = respectRange(cos * xTmp - sin * yTmp + offset.x);
    float y = respectRange(sin * xTmp + cos * yTmp + offset.y);
    return Point(x, y, p.type, p.enableLaser, p.wait);
}

void Project::SetNextPathAndRotation(unsigned int moveSpeed, bool enableMove, int curvatureLevel)
{
    if(!enableMove)
    {
        path = nullptr;
        return;
    }
    bool setSinCos = false;
    float previousX = 0.0f;
    float previousY = 0.0f;
    if(path !=  nullptr)
    {
        previousX = path->point.x;
        previousY = path->point.y;
        setSinCos = true;
    }
    SetNextPath(moveSpeed, curvatureLevel);
    if(setSinCos)
    {
        float dx = path->point.x - previousX;
        float dy = path->point.y - previousY;
        if(abs(dx) > 0.001f || abs(dy) > 0.001f)
        {
            float d = hypotf(dx, dy);
            rotateSin = dy / d;
            rotateCos = dx / d;
        }
    }
}

const PointWithMetadata* Project::next(unsigned int stepsSize, unsigned int moveSpeed, bool enableMove, int curvatureLevel)
{
    const PointWithMetadata* shapePoint = shape.next(stepsSize, curvatureLevel);
    if(shapePoint == nullptr)
    {
        SetNextPathAndRotation(moveSpeed, enableMove, curvatureLevel);
        return nullptr;
    }

    if(path == nullptr)
    {
        //animation is not configured
        return shapePoint;
    }
    p.point = rotateScaleAndShift(shapePoint->point, rotateSin, rotateCos, path->point, moveScale);
    p.isNextComponent = shapePoint->isNextComponent;

    return &p;
}

