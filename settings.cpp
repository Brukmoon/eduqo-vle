#include <QApplication>
#include "settings.h"

Settings::Settings(QObject *parent) : QSettings(QSettings::UserScope, QApplication::instance()->organizationName(),
                                                QApplication::instance()->applicationName(), parent)
{}

Settings::~Settings()
{}

void Settings::setValue(const QString &key, const QVariant &value)
{
    QSettings::setValue(key, value);
    emit settingsModified();
}

QVariant Settings::getValue(const QString &key, const QVariant &defValue) const
{
    QVariant val = QSettings::value(key, defValue);
    if(val.isNull() || !val.isValid()) return defValue;
    else
        return QSettings::value(key, defValue);
}
