#include "project.h"
#include "shapecollection.h"
#include <string>

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
    readPointSequenceV5(myfile, shape);
    readPointSequenceV5(myfile, move);
}

void Project::load(const char* file)
{
    std::ifstream myfile;
    myfile.open (file);
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
    myfile.close();
}

void Project::save(const char* file)
{
    std::ofstream myfile;
    myfile.open (file);
    myfile << "V5" << std::endl;
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

static int scaleAndShift(int value, int scale, int offset)
{
    value -= 2048;
    if(scale != 100)
    {
        value = value * scale / 100;
    }
    value = value + offset;
    value = value < 0? 0 : value;
    return value > 4095? 4095 : value;
}

void Project::restart()
{
    move.restart();
    shape.restart();
    path = nullptr;
}

void Project::SetNextPath()
{
    if(move.points.size() > 0)
    {
        path = move.next(1);
        while(path == nullptr)
        {
            path = move.next(1);
        }
    }
}

const PointWithMetadata* Project::next(unsigned int stepsSize)
{
    const PointWithMetadata* shapePoint = shape.next(stepsSize);
    if(shapePoint == nullptr)
    {
        SetNextPath();
        return nullptr;
    }

    if(path == nullptr)
    {
        //animation is not configured
        return shapePoint;
    }
    p.point = shapePoint->point;
    p.point.x = scaleAndShift(shapePoint->point.x, 25, path->point.x);
    p.point.y = scaleAndShift(shapePoint->point.y, 25, path->point.y);
    p.isNextComponent = shapePoint->isNextComponent;

    return &p;
}

