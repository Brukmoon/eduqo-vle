#include <QCryptographicHash>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include "login.h"
#include "settings.h"

bool Login::validateLogin(User* user) {
    if(user->getUsername() == "" || user->getPassword() == "") {
        qDebug() << "You must first set username and password.";
        return false;
    }
    Settings settings;
    if(!settings.getValue("user/rememberMe", false).toBool())
    {
        QCryptographicHash crypt(QCryptographicHash::Sha3_512);
        QString salt = getSalt(user->getUsername());
        if(salt == "0" || salt == "-1") { return false; }
         crypt.addData(QByteArray(QString(salt + user->getPassword()).toUtf8()));
         user->setPassword(crypt.result().toHex());
    }
    if(getPassword(user->getUsername())==user->getPassword()) {
        return true;
    } else {
        return false;
    }
}

QString Login::getSalt(const QString &username) const
{
    QSqlQuery query;
    query.prepare("SELECT salt FROM users WHERE username=:usr");
    query.bindValue(0, username);
    if(!query.exec()) {
        qDebug() << "Salt couldn't be acquired.";
        return "0";
    }
    if(!query.first()) {
        return "-1";
    }
    return query.value(0).toString();
}

QString Login::getPassword(const QString &username) const
{
    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE username=:usr");
    query.bindValue(0, username);
    if(!query.exec()) {
        qDebug() << "Password couldn't be acquired.";
        return "0";
    }
    query.first();
    return query.value(0).toString();
}
