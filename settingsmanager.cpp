#include <QSettings>
#include "settingsmanager.h"

void SettingsManager::writeSetting(const QString &key, const QVariant &value)
{
    QSettings settings("eduqo", "EduQo");
    settings.setValue(key, value);
}

void SettingsManager::loadSettings()
{
}
