#ifndef COLLECTIONLOADER_H
#define COLLECTIONLOADER_H

#include "shapecollection.h"

class Project
{
public:
    Project();
    ~Project();

    void save(const char* file);
    void load(const char* file);
    const PointWithMetadata* next(unsigned int stepsSize, unsigned int moveSpeed);
    void restart();
    void clear();
    bool isEmpty();

    ShapeCollection shape;
    ShapeCollection move;

private:
    void loadV2(std::ifstream &myfile);
    void loadV3(std::ifstream &myfile);
    void loadV4(std::ifstream &myfile);
    void loadV5(std::ifstream &myfile);
    void SetNextPath(unsigned int moveSpeed);
    
    const PointWithMetadata* path;
    PointWithMetadata p;
    void readPointSequenceV5(std::ifstream &myfile, ShapeCollection& sc);
};

#endif // COLLECTIONLOADER_H
