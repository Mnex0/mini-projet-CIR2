

#include "RoutePoint.h"
#include "City.h"

using namespace std;

class Route
{
public:
    Route();
    ~Route() {};

private:
    City startCity;
    City endCity;
};