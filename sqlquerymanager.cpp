#include "sqlquerymanager.h"
#include <QSqlQuery>

bool SqlQueryManager::query(QString queryString)
{
    QSqlQuery query;
    query.prepare(queryString);
    //query.bindValue(0, username);
    //query.bindValue(1, verifier);
    if(!query.exec()) return false;
    query.first();
}
