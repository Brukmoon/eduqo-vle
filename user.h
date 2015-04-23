#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>

class User : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString password READ getPassword WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(bool online READ isOnline WRITE setOnline NOTIFY onlineChanged)
public:
    explicit User(QObject *parent = 0);
    virtual ~User();
    QString getUsername() const { return username; }
    QString getPassword() const { return passwordHash; }
    bool isOnline() const { return online; }
signals:
    void loginSuccess();
    void loginFailed();
    void skipLogin();
    void usernameChanged();
    void passwordChanged();
    void onlineChanged();
public slots:
    void login();
    void logout();
    void setUsername(const QString &username) { this->username = username; emit usernameChanged(); }
    void setPassword(const QString &password) { passwordHash = password; emit passwordChanged(); }
    void setOnline(const bool online) { this->online = online; emit onlineChanged(); }
private:
    QString username;
    QString passwordHash;
    bool online;
};

#endif // USER_H
