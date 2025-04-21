
#include "BDD.h"

#include <iostream>
#include <vector>
#include <string>
#include <locale>
#include <QImage>
#include <QPainter>

using namespace std;

BDD::BDD(string host, string nomBDD, string username, string password)
{
    this->carte = Carte();
    sql::Driver *driver = get_driver_instance();
    con = driver->connect(host, username, password);

    con->setSchema(nomBDD);

    setlocale(LC_ALL, "C");
}

BDD::~BDD()
{
    std::cout << "Fermeture connection\n";
    delete con;
}

void BDD::ajouterContour()
{

    int generate_png_file = 1;

    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res = stmt->executeQuery("select * from contour");
    cout << res;
    vector<PointContour> points;
    while (res->next())
    {
        points.push_back(PointContour(res->getDouble(3), res->getDouble(2)));
    }

    if (generate_png_file)
    {
        QImage image(500, 500, QImage::Format_ARGB32);
        image.fill(Qt::white);

        QPainter painter(&image);
        painter.setPen(Qt::green);

        float X = 0, Y = 0, lastX = 0, lastY = 0;
        double minLatFloat = 0, maxLatFloat = 0, minLonFloat = 0, maxLonFloat = 0;
        sql::ResultSet *limits = stmt->executeQuery("select min(lat), max(lat), min(lon), max(lon) from contour");
        limits->next();
        minLatFloat = limits->getDouble(1);
        maxLatFloat = limits->getDouble(2);
        minLonFloat = limits->getDouble(3);
        maxLonFloat = limits->getDouble(4);

        for (auto &point : points)
        {
            X = (maxLatFloat - point.getLat()) * 100;
            Y = (maxLonFloat - point.getLon()) * 100;
            if (lastX != 0 && lastY != 0)
            {
                painter.drawLine(QPointF(lastY, lastX), QPointF(Y, X));
            }
            lastX = X;
            lastY = Y;
        }

        image.save("Carte.png");

        delete limits;
    }

    delete res;
    delete stmt;

    this->carte.setContour(points);
}

void BDD::ajouterWaypoints()
{

    int generate_png_file = 1;

    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res = stmt->executeQuery("select * from waypoint");
    cout << res;
    vector<waypoint> pointsPassage;
    float lat = 0, lon = 0;
    string nom = "";
    while (res->next())
    {
        lat = res->getDouble(2);
        lon = res->getDouble(3);
        string nom = res->getString(1);
        pointsPassage.push_back(waypoint(res->getDouble(2), res->getDouble(3), res->getString(1)));
        waypoint wayP = waypoint(lat, lon, nom);
        this->carte.ajouterWaypoint(wayP);
    }

    if (generate_png_file)
    {
        QImage image;
        image.load("Carte.png");
        QPainter painter(&image);
        QPen pen(Qt::black, 3);
        painter.setPen(pen);

        float X = 0, Y = 0;
        double minLatFloat = 0, maxLatFloat = 0, minLonFloat = 0, maxLonFloat = 0;
        sql::ResultSet *limits = stmt->executeQuery("select min(lat), max(lat), min(lon), max(lon) from contour");
        limits->next();
        minLatFloat = limits->getDouble(1);
        maxLatFloat = limits->getDouble(2);
        minLonFloat = limits->getDouble(3);
        maxLonFloat = limits->getDouble(4);

        for (auto &point : pointsPassage)
        {
            X = (maxLatFloat - point.getLat()) * 100;
            Y = (maxLonFloat - point.getLon()) * 100;
            cout << "LAT : " << point.getLat() << " LON : " << point.getLon() << endl;
            painter.drawPoint(Y, X);
        }
        image.save("Carte.png");

        delete limits;
    }

    delete res;
    delete stmt;
}

void BDD::ajouterVilles()
{

    int generate_png_file = 1;

    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res = stmt->executeQuery("select * from waypoint join ville where waypoint.nom = ville.nom");
    cout << res;
    vector<waypoint> PointsVilles;
    string nom = "";
    int CP = 0, nb_habs = 0;
    string url = "";
    float lat = 0, lon = 0;
    while (res->next())
    {
        lat = res->getDouble(2);
        lon = res->getDouble(3);
        nom = res->getString(4);
        CP = res->getInt(5);
        nb_habs = res->getInt(6);
        url = res->getString(7);
        Ville ville = Ville(nom, CP, nb_habs, url);
        ville.setparentCarte(&(this->carte));
        waypoint wayP = waypoint(lat, lon, nom);
        ville.setPoint(wayP);
        PointsVilles.push_back(wayP);
        this->carte.ajouterVille(ville);
    }

    if (generate_png_file)
    {
        QImage image;
        image.load("Carte.png");
        QPainter painter(&image);
        QPen pen(Qt::red, 4);
        painter.setPen(pen);

        float X = 0, Y = 0;
        double minLatFloat = 0, maxLatFloat = 0, minLonFloat = 0, maxLonFloat = 0;
        sql::ResultSet *limits = stmt->executeQuery("select min(lat), max(lat), min(lon), max(lon) from contour");
        limits->next();
        minLatFloat = limits->getDouble(1);
        maxLatFloat = limits->getDouble(2);
        minLonFloat = limits->getDouble(3);
        maxLonFloat = limits->getDouble(4);

        for (auto &point : PointsVilles)
        {
            X = (maxLatFloat - point.getLat()) * 100;
            Y = (maxLonFloat - point.getLon()) * 100;
            painter.drawPoint(Y, X);
        }
        image.save("Carte.png");

        delete limits;
    }

    delete res;
    delete stmt;
}

void BDD::ajouterRoutes()
{
    int generate_png_file = 1;

    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res = stmt->executeQuery("select * from route");
    vector<Route> routes;
    while (res->next())
    {
        string nomDebut = res->getString(1);
        string nomFin = res->getString(2);
        int dist = res->getInt(3);

        waypoint *debut = this->carte.getWaypointByName(nomDebut);
        waypoint *fin = this->carte.getWaypointByName(nomFin);
        cout << "DONC LAT AND LON = " << debut->getLat() << " AND " << debut->getLon() << endl;
        if (debut && fin)
        {
            Route route = Route();
            route.setRoute(*debut, *fin, dist);
            routes.push_back(route);
            this->carte.ajouterRoute(route);
        }
    }
    if (generate_png_file)
    {
        QImage image;
        image.load("Carte.png");
        QPainter painter(&image);
        QPen pen(Qt::blue, 1);
        painter.setPen(pen);

        float X = 0, Y = 0;
        double minLatFloat = 0, maxLatFloat = 0, minLonFloat = 0, maxLonFloat = 0;
        sql::ResultSet *limits = stmt->executeQuery("select min(lat), max(lat), min(lon), max(lon) from contour");
        limits->next();
        minLatFloat = limits->getDouble(1);
        maxLatFloat = limits->getDouble(2);
        minLonFloat = limits->getDouble(3);
        maxLonFloat = limits->getDouble(4);

        for (auto &route : routes)
        {
            float X1 = (maxLatFloat - route.getWaypointDebut().getLat()) * 100;
            float Y1 = (maxLonFloat - route.getWaypointDebut().getLon()) * 100;
            float X2 = (maxLatFloat - route.getWaypointFin().getLat()) * 100;
            float Y2 = (maxLonFloat - route.getWaypointFin().getLon()) * 100;

            painter.drawLine(QPointF(Y1, X1), QPointF(Y2, X2));
        }

        image.save("Carte.png");

        delete limits;
    }

    delete res;
    delete stmt;
}

Ville::Ville(string nom, int CP, int nb_habs, string url)
{
    this->nomVille = nom;
    this->codePostal = CP;
    this->nb_habitants = nb_habs;
    this->weburl = url;
    this->Point = waypoint();
}

waypoint::waypoint(float lat, float lon, string nom)
{
    this->lat = lat;
    this->lon = lon;
    this->nom = nom;
}

waypoint *Carte::getWaypointByName(string nom)
{
    vector<waypoint> &waypoints = *(this->getWaypoints());
    for (auto &wayP : waypoints)
    {
        if (wayP.getNom() == nom)
        {
            cout << "TROUVE = " << wayP.getLat() << " AND LON = " << wayP.getLon() << endl;
            return &wayP;
        }
    }
    return nullptr;
}
