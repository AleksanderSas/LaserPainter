#include "bezier.h"
#include "math.h"
#include <iostream>
#include <fstream>

Bezier::Bezier()
{

}

Bezier::~Bezier() { }

void Bezier::Add(unsigned int x, unsigned int y)
{
    Point p;
    p.x = x;
    p.y = y;
    curves.push_back(p);
}

void Bezier::deletePoint(unsigned int x, unsigned int y, int squerDis)
{
    for(auto iter = curves.begin(); iter != curves.end(); iter++)
    {
        int dist = (iter->x - x) * (iter->x - x) + (iter->y - y) * (iter->y - y);
        if(dist < squerDis)
        {
            curves.erase(iter);
            return;
        }
    }
}

Point* Bezier::getPoint(unsigned int x, unsigned int y, int squerDis)
{
    for(Point& p : curves)
    {
        int dist = (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y);
        if(dist < squerDis)
            return &p;
    }
    return nullptr;
}

Point* Bezier::getOrAddPoint(unsigned int x, unsigned int y, int squerDis)
{
    for(Point& p : curves)
    {
        int dist = (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y);
        if(dist < squerDis)
            return &p;
    }
    Add(x, y);
    return &curves[curves.size() - 1];
}

void Bezier::load(const char* file)
{
    std::ifstream myfile;
    myfile.open (file);
    std::string version;
    myfile >> version;
    if(version != "V1")
    {
        throw "only V1 standard is supported";
    }
    while(myfile.good())
    {
        int x, y;
        myfile >> x;
        myfile >> y;
        Add(x, y);
    }
    myfile.close();
}

void Bezier::save(const char* file)
{
    std::ofstream myfile;
    myfile.open (file);
    myfile << "V1" << std::endl;
    for(Point &p : curves)
    {
        myfile << p.x << " " << p.y << std::endl;
    }
    myfile.close();
}

void Bezier::clear()
{
    curves.clear();
}





