#include "configuration.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

Configuration::Configuration()
{
    std::ifstream input;
    input.open (CONFIG_FILE);

    while(input.good())
    {
        std::string key, value;
        input >> key >> value;

        if(key == CNF_DIR)
        {
           dir = value;
           continue;
        }

        if(key == CNF_FILE)
        {
           file = value;
           continue;
        }

        if(key == CNF_REPEARS)
        {
           repeats = atoi(value.c_str());
           if(repeats == 0)
               errors += value + " is not correct integer.\n";
           continue;
        }

        if(key == CNF_RESOLUTION)
        {
           resolution = atoi(value.c_str());
           if(resolution == 0)
               errors += value + " is not correct integer.\n";
           continue;
        }
        if(!key.empty())
            errors += key + " is not valid configuration.\n";
    }

    input.close();
}

Configuration::~Configuration()
{
    std::ofstream output;
    output.open (CONFIG_FILE);

    if(!dir.empty())
        output << CNF_DIR << " " << dir << std::endl;
    if(!file.empty())
        output << CNF_FILE << " " << file << std::endl;
    output << CNF_REPEARS << " " << repeats << std::endl;
    output << CNF_RESOLUTION << " " << resolution << std::endl;

    output.close();
}

std::string Configuration::GetErrors()
{
    return errors;
}
