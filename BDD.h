#include "Carte.h"
#include "Contour.h"

class BDD
{
public:
    // cteur
    // Dteur
    Carte getCarte();
    void ajouterPointsContour(Carte &carte);

private:
    sql::Connection *con;
}

