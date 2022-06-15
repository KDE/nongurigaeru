#include "NGBeacon.h"
#include "NGBeaconController.h"

struct NGBeacon::Private
{
	QPointer<NGBeaconController> controller = nullptr;
	QString beaconID;
	QJSValue dataCallback;
};

NGBeacon::NGBeacon(QQuickItem* parent) : QQuickItem(parent), d(new Private)
{
}

NGBeacon::~NGBeacon()
{
	if (d->controller) d->controller->delBeacon(this);
}

NGBeaconController* NGBeacon::controller() const
{
	return d->controller;
}

void NGBeacon::setController(NGBeaconController* controller)
{
	if (d->controller == controller)
		return;

	if (d->controller != nullptr) {
		d->controller->delBeacon(this);
	}
	d->controller = controller;
	d->controller->addBeacon(this);
	Q_EMIT controllerChanged();
}

QString NGBeacon::beaconID() const
{
	return d->beaconID;
}

void NGBeacon::setBeaconID(const QString& beaconID)
{
	if (d->beaconID == beaconID)
		return;

	d->beaconID = beaconID;
	Q_EMIT beaconIDChanged();
}

QJSValue NGBeacon::dataCallback() const
{
	return d->dataCallback;
}

void NGBeacon::setDataCallback(QJSValue dataCallback)
{
	d->dataCallback = dataCallback;
	Q_EMIT dataCallbackChanged();
}

QVariant NGBeacon::data() const
{
	return d->dataCallback.call().toVariant();
}

