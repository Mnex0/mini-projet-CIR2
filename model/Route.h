
#include "Ville.h"

using namespace std;

class Route
{
public:
    Route() {};
    ~Route() {}
    waypoint getWaypointDebut() { return this->WaypointDebut; }
    waypoint getWaypointFin() { return this->WaypointFin; }
    int getDistance() { return this->distance; }
    void setRoute(waypoint debut, waypoint fin, int dist) { this->WaypointDebut = debut; this->WaypointFin= fin; this->distance = dist; }

private:
    waypoint WaypointDebut;
    waypoint WaypointFin;
    int distance;
};