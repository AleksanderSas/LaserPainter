#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>

#define CNF_RESOLUTION "RESOLUTION:"
#define CNF_MOVE_SPEED "MOVE_SPEED:"
#define CNF_REPEARS "REPEATS:"
#define CNF_DIR "DIR:"
#define CNF_FILE "FILE:"
#define CNF_SCALE "SCALE:"

#define CONFIG_FILE "./config"

class Configuration
{
public:
    Configuration();
    ~Configuration();

    std::string GetErrors();

    std::string dir = "/home", file = "";
    int repeats = 100;
    int resolution = 25;
    int moveSpeed = 3;
    int scale = 100;

private:
    std::string errors;
};

#endif // CONFIGURATION_H
