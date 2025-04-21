
#include <iostream>
#include <string>
#include <vector>
#include <clocale>

#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "Carte.h"

class BDD
{
public:
    BDD(string host, string dbName, string username, string password);
    ~BDD();

    void ajouterRoutes();
    void ajouterContour();
    void ajouterVilles();
    void ajouterWaypoints();
    Carte getCarte() { return this->carte; }
    vector<Ville> getVilles() { return this->carte.getVilles(); }
    vector<Route> getRoutes() { return this->carte.getRoutes(); }
    Contour getContour() { return this->carte.getContour(); }

private:
    Carte carte;
    sql::Connection *con;
};
