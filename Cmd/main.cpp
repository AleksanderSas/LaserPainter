#include "../LaserPainter/shapecollection.h"
#include "../LaserPainter/hardwareconnector.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void printHelp()
{
    printf("run <file> <options>\n");
    printf("-t <integer>  --- repeat number\n" );
    printf("-r <integer>  --- resolution\n" );
}

bool tryParse(const char* arg, int &value, int argc, char *argv[], int &i)
{
    if(strcmp(arg, argv[i]) == 0)
    {
        if(argc <= i + 1)
        {
            printf("missing value for %s\n", arg);
            printHelp();
            exit(1);
        }
        
        int valueTmp = atoi(argv[i + 1]);
        i++;
        value = valueTmp;
        
        if(valueTmp == 0)
        {
            printf("argument %s is not valid integer\n", argv[i + 1]);
            printHelp();
            exit(1);
        }
        return true;
    }
    return false;
}

int main(int argc, char *argv[]){
 
    int repeats = 300;
    int resolution = 200;
    if(argc < 2)
    {
        printHelp();
    }
    for(int i = 2; i < argc; i++)
    {
        if(tryParse("-t", repeats, argc, argv, i))
        {
            continue;
        }
        
        if(tryParse("-r", resolution, argc, argv, i))
        {
            continue;
        }
        
        printf("unknown argument %s\n", argv[i]);
        printHelp();
    }
    
    HardwareConnector connector;
    ShapeCollection shapeCollection;
    shapeCollection.load(argv[1]);
    
    connector.draw(shapeCollection, resolution, repeats);
   return 0;
}

