#ifndef SETTINGS_H
#define SETTINGS_H
#include <QSettings>

class Settings : public QSettings
{
    Q_OBJECT
public:
    explicit Settings(QObject* parent = 0);
    ~Settings();
signals:
    void settingsModified();
public slots:
    void setValue(const QString &key, const QVariant &value = QVariant());
    void remove(const QString &key) { QSettings::remove(key); }
public:
    Q_INVOKABLE QVariant getValue(const QString &key, const QVariant &defValue = QVariant()) const;
};

#endif // SETTINGS_H
