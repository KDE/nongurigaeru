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
		} else if (properties.contains(property.name())) {
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
			if (!state.hasGroup(prop.name()) || !(state.group(prop.name()).groupList().length() > 0)) {
				if (prop.isRequired()) {
					// TOOD: handle failed restoration
				}
				prop.write(on, QVariant::fromValue(nullptr));
				continue;
			}

			auto id = QUuid::fromString(state.group(prop.name()).groupList()[0]);
			auto group = state.group(prop.name()).group(state.group(prop.name()).groupList()[0]);
			auto restorer = getRestorer(group);
			restorer->restore(id, group, [&](QObject* ret) {
				prop.write(on, QVariant::fromValue(ret));
				delete restorer;
			});
		} else {
			qFatal("Sorry, NGLib can't automatically restore scalar properties yet! This shouldn't be here on release.");
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
			auto propertyGroup = state.group(prop.name());

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
