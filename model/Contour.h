
#include "PointContour.h"
#include <vector>

using namespace std;

class Contour
{
public:
    Contour();
    ~Contour() {};

private:
    vector<PointContour> outlinePoints;
};