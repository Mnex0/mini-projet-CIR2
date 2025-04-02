
#include "Outline.h"
#include "Route.h"

class Map
{
public:
    Map();
    ~Map() {};

private:
    vector<City> Cities;
    Outline outline;
    vector<Route> Routes;
};