
#include "Contour.h"
#include "Route.h"

class Carte
{
public:
    Carte() {};
    ~Carte() {}

    vector<Ville> getVilles() { return this->Villes; }
    Contour getContour() { return this->contour; }
    vector<Route> getRoutes() { return this->Routes; }
    //vector<waypoint> getWaypoints() { return &(this->Waypoints); }
    // Return a reference to the vector of waypoints
    vector<waypoint> getWaypoints() { return this->Waypoints; }
    void ajouterRoute(Route route) { this->Routes.push_back(route); };
    void ajouterVille(Ville ville) { this->Villes.push_back(ville); }
    void setContour(vector<PointContour> points) { this->contour.setPoints(points); }
    void ajouterWaypoint(waypoint wayP) { this->Waypoints.push_back(wayP); }
    waypoint *getWaypointByName(string nom);

private:
    vector<Ville> Villes;
    Contour contour;
    vector<Route> Routes;
    vector<waypoint> Waypoints;
};