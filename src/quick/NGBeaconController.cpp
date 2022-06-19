// SPDX-FileCopyrightText: 2022 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#include <QtMath>

#include "NGBeaconController.h"
#include "NGBeaconControllerDelegate.h"
#include "NGBeacon.h"

inline qreal hypotenuse(qreal x, qreal y)
{
	return qSqrt(qPow(x, 2) + qPow(y, 2));
}

inline qreal distance(const QPointF& point, const QRectF& rect)
{
	qreal xMin, yMin, xMax, yMax, pX, pY;
	rect.getCoords(&xMin, &yMin, &xMax, &yMax);

	pX = point.x();
	pY = point.y();

	const auto dx = qMax(qMax(xMin - pX, pX - xMax), 0.0);
	const auto dy = qMax(qMax(yMin - pY, pY - yMax), 0.0);

	return hypotenuse(dx, dy);
}

struct NGBeaconController::Private
{
	QString activeBeaconID;
	QPointer<NGBeacon> activeBeacon;
	QList<NGBeacon*> beacons;
	NGBeaconControllerDelegate* delegate;
};

NGBeaconController::NGBeaconController(QQuickItem* parent) : QQuickItem(parent), d(new Private)
{
	setFlag(QQuickItem::ItemAcceptsDrops, true);
}

NGBeaconController::~NGBeaconController()
{
}

void NGBeaconController::addBeacon(NGBeacon* beacon)
{
	d->beacons << beacon;
}

void NGBeaconController::delBeacon(NGBeacon* beacon)
{
	d->beacons.removeAll(beacon);
}

QString NGBeaconController::activeBeaconID() const
{
	return d->activeBeaconID;
}


void NGBeaconController::computeActiveBeacon(const QPointF& point)
{
	if (d->beacons.size() == 0)
		return;

	using TheTuple = QPair<NGBeacon*, QRectF>;
	QList<TheTuple> beacons;
	beacons.reserve(d->beacons.size());

	for (auto* beacon : d->beacons) {
		beacons << qMakePair(beacon, beacon->mapRectToItem(this, beacon->boundingRect()));
	}

	std::sort(beacons.begin(), beacons.end(), [&point](const TheTuple& lhs, const TheTuple& rhs) {
		return distance(point, lhs.second) < distance(point, rhs.second);
	});
	const auto& theClosest = beacons.constFirst();

	if (theClosest.first->beaconID() == d->activeBeaconID)
		return;

	d->activeBeaconID = theClosest.first->beaconID();
	Q_EMIT activeBeaconIDChanged();
	d->activeBeacon = theClosest.first;
}

NGBeaconControllerDelegate* NGBeaconController::delegate() const
{
	return d->delegate;
}

void NGBeaconController::setDelegate(NGBeaconControllerDelegate* delegate)
{
	if (d->delegate == delegate)
		return;

	d->delegate = delegate;
	Q_EMIT delegateChanged();
}

void NGBeaconController::dragEnterEvent(QDragEnterEvent* event)
{
	computeActiveBeacon(event->posF());
	event->acceptProposedAction();

	if (d->delegate) d->delegate->dragEnterEvent(event);
}

void NGBeaconController::dragMoveEvent(QDragMoveEvent* event)
{
	computeActiveBeacon(event->posF());

	if (d->delegate) d->delegate->dragMoveEvent(event);
}

void NGBeaconController::dragLeaveEvent(QDragLeaveEvent* event)
{
	if (d->activeBeaconID.isEmpty())
		return;

	d->activeBeaconID = QString();
	Q_EMIT activeBeaconIDChanged();

	if (d->delegate) d->delegate->dragLeaveEvent(event);
}

void NGBeaconController::dropEvent(QDropEvent* event)
{
	if (d->activeBeaconID.isEmpty())
		return;

	d->activeBeaconID = QString();
	Q_EMIT activeBeaconIDChanged();

	if (d->delegate) d->delegate->dropEvent(d->activeBeacon, event);
}

