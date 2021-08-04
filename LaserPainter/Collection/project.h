#ifndef COLLECTIONLOADER_H
#define COLLECTIONLOADER_H

#include "shapecollection.h"

class Project
{
public:
    Project();
    ~Project();

    void save(const char* file);
    void load(std::string &file);
    const PointWithMetadata* next(unsigned int stepsSize);
    void restart();
    void clear();
    bool isEmpty();

    ShapeCollection shape;
    ShapeCollection move;
    int moveScale;

private:
    void loadV2(std::ifstream &myfile);
    void loadV3(std::ifstream &myfile);
    void loadV4(std::ifstream &myfile);
    void loadV5(std::ifstream &myfile);
    void SetNextPath();
    
    const PointWithMetadata* path;
    PointWithMetadata p;
    void readPointSequenceV5(std::ifstream &myfile, ShapeCollection& sc);
};

#endif // COLLECTIONLOADER_H
