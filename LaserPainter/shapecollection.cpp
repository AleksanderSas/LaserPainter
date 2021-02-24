#include "shapecollection.h"
#include <iostream>
#include <fstream>
#include "bezier.h"
#include "circle.h"
#include "line.h"

ShapeCollection::ShapeCollection()
{

}

ShapeCollection::~ShapeCollection()
{
    clear();
}

AbstractShape* createShape(ShapeType type)
{
    switch (type) {
    case ShapeType::BEZIER: return new Bezier();
    case ShapeType::LINE: return new Line();
    case ShapeType::CIRCLE: return new Circle();
    }
}

void ShapeCollection::Add(unsigned int x, unsigned int y, ShapeType type)
{
    Point p;
    p.x = x;
    p.y = y;
    points.push_back(p);

    if(shapes.size() == 0) //first point
    {
        AbstractShape *shape = createShape(type);
        shape->offset = 0;
        shape->pointNumber = 1;
        shapes.push_back(shape);
    }
    else if(shapes[shapes.size() - 1]->getType() != type) //change shape type
    {
        AbstractShape *shape = createShape(type);
        shape->offset = points.size() - 2;
        shape->pointNumber = 2;
        shapes.push_back(shape);
    }
    else // continue current shape
    {
        shapes[shapes.size() - 1]->pointNumber++;
    }
}

void ShapeCollection::deletePoint(unsigned int x, unsigned int y, unsigned int squerDis)
{
    unsigned int idx = 0;
    for(auto iter = points.begin(); iter != points.end(); iter++)
    {
        unsigned int dist = (iter->x - x) * (iter->x - x) + (iter->y - y) * (iter->y - y);
        if(dist < squerDis)
        {
            points.erase(iter);
            idx = iter - points.begin() + 1;
            break;
        }
    }

    auto iter = shapes.begin();
    for(; iter != shapes.end(); iter++)
    {
        if(idx <= (*iter)->offset + (*iter)->pointNumber)
        {
            (*iter)->pointNumber--;
            if((*iter)->pointNumber < 2)
            {
                //TODO: remove
            }
            break;
        }
    }
    iter++;
    for(; iter != shapes.end(); iter++)
    {
        (*iter)->offset--;
    }
}

Point* ShapeCollection::getPoint(unsigned int x, unsigned int y, unsigned int squerDis)
{
    for(Point& p : points)
    {
        unsigned int dist = (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y);
        if(dist < squerDis)
            return &p;
    }
    return nullptr;
}

Point* ShapeCollection::getOrAddPoint(unsigned int x, unsigned int y, ShapeType type, unsigned int squerDis)
{
    for(Point& p : points)
    {
        unsigned int dist = (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y);
        if(dist < squerDis)
            return &p;
    }
    Add(x, y, type);
    return &points[points.size() - 1];
}

void ShapeCollection::loadV1(std::ifstream &myfile)
{
    while(myfile.good())
    {
        unsigned int x, y;
        myfile >> x;
        myfile >> y;
        Add(x, y, ShapeType::BEZIER);
    }
}

void ShapeCollection::loadV2(std::ifstream &myfile)
{
    while(myfile.good())
    {
        unsigned int x, y, lineType;
        myfile >> lineType;
        myfile >> x;
        myfile >> y;
        Add(x, y, (ShapeType)lineType);
    }
}

void ShapeCollection::load(const char* file)
{
    std::ifstream myfile;
    myfile.open (file);
    std::string version;
    myfile >> version;
    if(version != "V1" && version != "V2")
    {
        throw "only V1 and V2 standards are supported";
    }
    if(version == "V1")
        loadV1(myfile);
    if(version == "V2")
        loadV2(myfile);
    myfile.close();
}

void ShapeCollection::save(const char* file)
{
    std::ofstream myfile;
    myfile.open (file);
    myfile << "V2" << std::endl;
    for(AbstractShape *s : shapes)
    {
        if(s->offset == 0)
        {
            myfile << s->getType() << " " << points[0].x << " " << points[0].y << std::endl;
        }
        for(unsigned int i = s->offset + 1; i < s->offset + s->pointNumber; i++)
        {
            myfile << s->getType() << " " << points[i].x << " " << points[i].y << std::endl;
        }
    }
    myfile.close();
}

void ShapeCollection::clear()
{
    points.clear();
    for(AbstractShape *shape : shapes)
    {
        delete shape;
    }
    shapes.clear();
}

unsigned int ShapeCollection::getTotalWeigth()
{
    unsigned int totalWeight = 0;
    for(AbstractShape *shape : shapes)
    {
        totalWeight += shape->getWeigth();
    }
    return totalWeight;
}

const Point* ShapeCollection::next(unsigned int steps)
{
    if(currectVisitor == nullptr)
    {
        currentShape = 0;
        unsigned int visitorSteps = steps * shapes[currentShape]->getWeigth() / getTotalWeigth();
        currectVisitor = shapes[currentShape]->getVisitor(visitorSteps);
    }

    const Point* p = currectVisitor->next(points);
    if(p == nullptr)
    {
        delete  currectVisitor;
        if(++currentShape < shapes.size())
        {
            unsigned int visitorSteps = steps * shapes[currentShape]->getWeigth() / getTotalWeigth();
            currectVisitor = shapes[currentShape]->getVisitor(visitorSteps);
            //assume 'next' will return none-null value
            return currectVisitor->next(points);
        }
        currectVisitor = nullptr;
        return nullptr;
    }
    return p;
}
