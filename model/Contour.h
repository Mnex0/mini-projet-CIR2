
#include "PointContour.h"
#include <vector>

using namespace std;

class Contour
{
public:
    Contour() {};
    ~Contour() {}
    void ajouterPoint(PointContour point) { this->PointsContour.push_back(point); }
    vector<PointContour> getPoints() { return this->PointsContour; }
    void setPoints(vector<PointContour> points) { this->PointsContour = points; }

private:
    vector<PointContour> PointsContour;
};