#include <iostream>
#include <string>
#include <vector>
#include <clocale>

#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "Map.h"

class DB
{
public:
    DB(string host, string dbName, string username, string password);
    DB() {}
    ~DB();

    Map selectMap();
    void addRoute(Map &map);
    void addCity(Route &mur);
    Map getMap();
    void insertMap(Map &map);

private:
    Map map;
    sql::Connection *con;
};