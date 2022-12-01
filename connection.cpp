#include "connection.h"

connection::connection()
{

}

bool connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projet");//inserer le nom de la source de données ODBC
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("Lina1111*");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
