#pragma once

#include <QGuiApplication>
#include <QString>

#include <KSharedConfig>

static const auto nglibRestorationKey = QStringLiteral("NGLibRestoration");
static const auto nglibRestorationClassKey = QStringLiteral("NGLibRestorationClass");

inline QString configName(const QString& id, const QString& key)
{
	return QLatin1String("session/%1_%2_%3").arg(QGuiApplication::applicationName(), id, key);
}

inline KSharedConfig::Ptr sessionRestorationConfig()
{
	return KSharedConfig::openConfig(configName(qApp->sessionId(), qApp->sessionId()), KConfig::SimpleConfig);
}
