#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>

#define CNF_RESOLUTION "RESOLUTION:"
#define CNF_REPEARS "REPEATS:"
#define CNF_DIR "DIR:"
#define CNF_FILE "FILE:"

#define CONFIG_FILE "./config"

class Configuration
{
public:
    Configuration();
    ~Configuration();

    std::string GetErrors();

    std::string dir = "/home", file = "";
    int repeats = 100, resolution = 300;

private:
    std::string errors;
};

#endif // CONFIGURATION_H
