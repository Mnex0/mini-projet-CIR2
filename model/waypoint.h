
#include <iostream>
#include <string>

using namespace std;

class waypoint
{
public:
    waypoint(float lat = 0, float lon = 0, string nom = "nom_waypoint");
    ~waypoint() {};
    float getLat() { return this->lat; }
    float getLon() { return this->lon; }
    string getNom() { return this->nom; }

private:
    float lat;
    float lon;
    string nom;
};