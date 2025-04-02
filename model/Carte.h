
#include "Contour.h"
#include "Route.h"

class Carte
{
public:
    Carte()
    {
        
    }
    ~Carte() {}

    vector<Ville> getVilles() { return this->Villes; }
    Contour getContour() { return this->contour; }
    vector<Route> getRoutes() { return this->Routes; }

private:
    vector<Ville> Villes;
    Contour contour;
    vector<Route> Routes;
};