#include <QDebug>
#include "user.h"
#include "login.h"

User::User(QObject *parent) : QObject(parent)
{
    username = "";
    passwordHash = "";
    setOnline(false);
}

User::~User()
{}

void User::login()
{
    Login login;
    if(login.validateLogin(this))
    {
        setOnline(true);
        emit loginSuccess();
    }
    else
        emit loginFailed();
}

void User::logout()
{
    qDebug() << __func__ << ": Not implemented.";
    setOnline(false);
}
