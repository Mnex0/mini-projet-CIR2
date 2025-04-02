#include "Carte.h"
#include "BDD.h"

BDD::BDD(std::string host, std::string nomBDD, std::string login, std::string pwd)
{
    /* Create a connection */
    sql::Driver *driver = get_driver_instance();
    con = driver->connect(host, login, pwd);

    /* Connect to the MySQL database */
    con->setSchema(nomBDD);

    setlocale(LC_ALL, "C");
}

BDD::~BDD()
{
    std::cout << "Fermeture connection\n";
    delete con;
}

Plan BDD::selectPlan(int id)
{
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res = stmt->executeQuery(
        "select * from plan where =" + std::to_string(id));
    res->next();
    Carte carte(res->getInt(1), res->getString(2),
                res->getInt(1), res->getDouble(2), res->getDoble(3));
    delete res;
    delete stmt;

    return contour;
}

Carte BDD::getCarte()
{
    Carte carte;
    //......
    this->ajouterPointsContour(carte.getContour());
    //......
    return carte;
}

void BDD::ajouterPointsContour(Carte &carte)
{
    "select * from contour order by num_pt" while (res->next())
    {
        Point pt(res->getInt(1), res->getDouble(2), res->getDoble(3)); // lat,long
    }
}