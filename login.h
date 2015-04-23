#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>
#include "user.h"

class Login : public QObject {
    Q_OBJECT
public:
    explicit Login(QObject* parent = 0) : QObject(parent) {}
public slots:
    bool validateLogin(User* user);
private:
    QString getSalt(const QString &username) const;
    QString getPassword(const QString &password) const;
};

#endif // LOGIN_H
