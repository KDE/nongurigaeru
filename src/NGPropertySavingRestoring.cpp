// SPDX-FileCopyrightText: 2022 Janet Blackquill <uhhadd@gmail.com>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#include <QMetaProperty>

#include "NGPropertySavingRestoring.h"
#include "NGSavable.h"
#include "NGPrivateConstants_p.h"

Q_LOGGING_CATEGORY(ngPropertySavingRestoring, "org.kde.nglib.propertysavingrestoring")

static QList<QMetaProperty> extractProperties(const QObject* on, const QStringList& properties)
{
	const auto metaObject = on->metaObject();
	const auto offset = metaObject->propertyOffset();
	const auto count = metaObject->propertyCount();

	QList<QMetaProperty> returnProperties;

	for (int propertyIndex = offset; propertyIndex < count; propertyIndex++) {
		const auto property = metaObject->property(propertyIndex);
		if (properties.isEmpty()) {
			returnProperties << property;
		} else if (properties.contains(QString::fromLocal8Bit(property.name()))) {
			returnProperties << property;
		}
	}

	return returnProperties;
}

void NGLIB_EXPORT NGPropertySavingRestoring::restoreProperties(const KConfigGroup& state, QObject* on, const QStringList& properties)
{
	const auto props = extractProperties(on, properties);

	for (auto& prop : props) {
		QMetaType type(prop.userType());

		if (auto metaObject = type.metaObject()) {
			const auto propName = QString::fromLocal8Bit(prop.name());

			if (!state.hasGroup(propName) || !(state.group(propName).groupList().length() > 0)) {
				if (prop.isRequired()) {
					// TOOD: handle failed restoration
				}
				prop.write(on, QVariant::fromValue(nullptr));
				continue;
			}

			auto id = QUuid::fromString(state.group(propName).groupList()[0]);
			auto group = state.group(propName).group(state.group(propName).groupList()[0]);
			auto restorer = getRestorer(group);
			restorer->restore(id, group, [&](QObject* ret) {
				prop.write(on, QVariant::fromValue(ret));
				delete restorer;
			});
		} else {
			auto variant = state.readEntry(prop.name(), QVariant(prop.metaType(), nullptr));
			prop.write(on, variant);
		}
	}
}

void NGLIB_EXPORT NGPropertySavingRestoring::saveProperties(KConfigGroup& state, const QObject* from, const QStringList& properties)
{
	const auto props = extractProperties(from, properties);

	for (auto& prop : props) {
		QMetaType type(prop.userType());

		if (auto metaObject = type.metaObject()) {
			auto objectValue = prop.read(from).value<QObject*>();
			auto propertyGroup = state.group(QString::fromLocal8Bit(prop.name()));

			if (auto saver = qobject_cast<NGSavable*>(objectValue)) {
				auto status = saveSavable(propertyGroup, saver);
				if (!status.ok) {
					// TODO: error handling
				}
			} else {
				qWarning(ngPropertySavingRestoring) << "Tried to save a non-savable class" << metaObject->className() << "when saving" << from;
			}
		} else {
			auto otherValue = prop.read(from);
			state.writeEntry(prop.name(), otherValue);
		}
	}
}
