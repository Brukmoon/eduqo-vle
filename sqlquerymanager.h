#ifndef SQLQUERYMANAGER_H
#define SQLQUERYMANAGER_H

#include <QObject>
QT_FORWARD_DECLARE_CLASS(QString)

class SqlQueryManager : public QObject
{
    Q_OBJECT
public:
    explicit SqlQueryManager(QObject *parent = 0) : QObject(parent) {}
    ~SqlQueryManager() {}
    bool query(QString query);
private:
};

#endif // SQLQUERYMANAGER_H
