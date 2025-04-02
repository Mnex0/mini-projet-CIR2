
#include "OutlinePoint.h"
#include <vector>

using namespace std;

class Outline
{
public:
    Outline();
    ~Outline() {};

private:
    vector<OutlinePoint> outlinePoints;
};