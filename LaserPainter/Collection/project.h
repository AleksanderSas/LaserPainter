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
    const PointWithMetadata* next(unsigned int stepsSize, unsigned int moveSpeed);
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
    void SetNextPath(unsigned int moveSpeed);
    
    const PointWithMetadata* path;
    float rotateSin = 0.0f;
    float rotateCos = 1.0f;
    PointWithMetadata p;
    void readPointSequenceV5(std::ifstream &myfile, ShapeCollection& sc);
    void SetNextPathAndRotation(unsigned int moveSpeed);
};

#endif // COLLECTIONLOADER_H
