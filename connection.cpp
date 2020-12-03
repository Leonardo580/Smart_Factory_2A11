#include "connection.h"
connection::connection()
{

}
bool connection::createconnect()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("SmartFactory");
    db.setUserName("aziz");
    db.setPassword("aziz");

    if(db.open())
        test=true;

    return test;
}
