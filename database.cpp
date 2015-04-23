#include <QSqlDatabase>
#include "database.h"

bool database::createConnection() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("eduqo");
    db.setUserName("root");
    db.setPassword("ascent");
    if(db.open()) return true;
    else return false;
}
