#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>

#define CNF_RESOLUTION "RESOLUTION:"
#define CNF_MOVE_SPEED "MOVE_SPEED:"
#define CNF_REPEARS "REPEATS:"
#define CNF_DIR "DIR:"
#define CNF_FILE "FILE:"
#define CNF_SCALE "SCALE:"
#define CNF_CURF_FACT "CURVATURE_FACTOR:"

#define CONFIG_FILE "./config"

class Configuration
{
public:
    Configuration();
    ~Configuration();

    std::string GetErrors();

    std::string dir = "/home", file = "";
    unsigned int repeats = 100;
    unsigned int resolution = 25;
    unsigned int curvatureFactor = 0;
    unsigned int moveSpeed = 3;
    unsigned int scale = 100;

private:
    std::string errors;
};

#endif // CONFIGURATION_H
