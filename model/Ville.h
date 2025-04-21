
#include "waypoint.h"

class Carte;

class Ville
{
public:
    Ville(string nom = "nom_ville", int CP = -1, int nb_habs = -1, string url = "url_ville");
    ~Ville() {}
    waypoint getPoint() { return this->Point; }
    string getNom() { return this->nomVille; }
    Carte *getCarte() { return this->carte; }
    void setparentCarte(Carte *carte) { this->carte = carte; }
    void setPoint(waypoint point) {this->Point = point;}

private:
    waypoint Point;
    string nomVille;
    int codePostal;
    int nb_habitants;
    string weburl;
    Carte *carte;
};