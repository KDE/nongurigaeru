#pragma once

#include <QGuiApplication>
#include <QLoggingCategory>
#include <QString>

#include <KSharedConfig>
#include <QDebug>
#include <QMetaMethod>

#include "NGRestorer.h"
#include "NGSavable.h"

Q_DECLARE_LOGGING_CATEGORY(ngPropertySavingRestoring)

static const auto nglibRestorationKey = QStringLiteral("NGLibRestoration");
static const auto nglibRestorationClassKey = QStringLiteral("NGLibRestorationClass");

inline QString configName(const QString& id, const QString& key)
{
	return QLatin1String("session/%1_%2_%3").arg(QGuiApplication::applicationName(), id, key);
}

inline KSharedConfig::Ptr sessionRestorationConfig()
{
	return KSharedConfig::openStateConfig(configName(qApp->sessionId(), qApp->sessionId()));
}

inline KSharedConfig::Ptr preferencesConfig()
{
	return KSharedConfig::openConfig();
}

inline NGSavable::SaveInformation saveSavable(KConfigGroup& parentGroup, const NGSavable* savable, bool child = true)
{
	auto destinationGroup = child ? parentGroup.group(savable->identifier().toString(QUuid::WithoutBraces)) : parentGroup;
	auto saveData = savable->save(destinationGroup);
	destinationGroup.writeEntry(nglibRestorationClassKey, saveData.className);
	return saveData;
}

inline NGRestorer* getRestorer(const KConfigGroup& from)
{
	auto restorationClass = from.readEntry<QString>(nglibRestorationClassKey, "");
	auto type = QMetaType::type(restorationClass.toStdString().c_str());

	if (type == QMetaType::UnknownType) {
		qWarning() << "Unknown restoration class" << restorationClass;
		return nullptr;
	}

	auto metaObject = QMetaType::metaObjectForType(type);
	if (metaObject->constructorCount() < 1) {
		qWarning() << "There are no invokable constructors defined for" << restorationClass;
	}

	bool found = false;
	for (int constructorIndex = 0; constructorIndex < metaObject->constructorCount(); constructorIndex++) {
		auto method = metaObject->constructor(constructorIndex);
		if (method.parameterCount() == 0) {
			found = true;
			break;
		}
	}

	if (!found) {
		qWarning() << "There are no invokable constructors with zero arguments defined for" << restorationClass;
	}

	NGRestorer* restorer = qobject_cast<NGRestorer*>(metaObject->newInstance());
	return restorer;
}
