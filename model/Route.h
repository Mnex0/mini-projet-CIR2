

#include "PointRoute.h"
#include "Ville.h"

using namespace std;

class Route
{
public:
    Route();
    ~Route() {};

private:
    Ville startCity;
    Ville endCity;
};