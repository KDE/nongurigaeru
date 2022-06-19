// SPDX-FileCopyrightText: 2022 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#pragma once

#include <QQuickItem>

#include "nglibquick_export.h"

class NGBeaconController;

/**

<summary>

A item that indicates a key spot to an NGBeaconController

</summary>

NGBeacon is an invisible item that should be scattered at key spots for a drag and drop operation.
For example, a list view might have NGBeacons before and after every item, and then on drop, the NGBeaconController
will find the nearest NGBeacon to the dropped position, to determine which item the new item should go by, and
whether it should go before and after that.

*/

class NGLIBQUICK_EXPORT NGBeacon : public QQuickItem
{

	Q_OBJECT

	/**

	The beacon controller that this NGBeacon belongs to.
	Ideally, the beacon controller should be a parent or a sibling of a parent to this item.

	*/
	Q_PROPERTY(NGBeaconController* controller READ controller WRITE setController NOTIFY controllerChanged REQUIRED)

	/**

	A unique identifier for this item, to distinguish it from other beacons.
	Example ID schemes include:

	<list>
		<item>
			A list, where beacons have IDs that are either <c>"before-" + index</c> or <c>"after" + index</c>
		</item>
		<item>
			A tree, where beacons have IDs that are either <c>"before-" + index</c>, <c>"after" + index</c>, <c>"append-in-" + index</c>, or <c>"prepend-in-" + index</c>
		</item>
	</list>

	Note that apps should not use the ID to carry data, instead, use the dataCallback, which can carry any data
	type and not just a string.

	*/
	Q_PROPERTY(QString beaconID READ beaconID WRITE setBeaconID NOTIFY beaconIDChanged REQUIRED)

	/**

	A function, that when called, will produce data to be read by the beacon controller and its delegate in order
	to decide what to do on a drop.

	This is a callback, rather than a property, to accomodate types with short lifespans, such as a QModelIndex.

	*/
	Q_PROPERTY(QJSValue dataCallback READ dataCallback WRITE setDataCallback NOTIFY dataCallbackChanged REQUIRED)

	struct Private;
	QScopedPointer<Private> d;

public:
	explicit NGBeacon(QQuickItem* parent = nullptr);
	~NGBeacon();

	NGBeaconController* controller() const;
	void setController(NGBeaconController* controller);
	Q_SIGNAL void controllerChanged();

	QString beaconID() const;
	void setBeaconID(const QString& beaconID);
	Q_SIGNAL void beaconIDChanged();

	QJSValue dataCallback() const;
	void setDataCallback(QJSValue dataCallback);
	Q_SIGNAL void dataCallbackChanged();

	/**

	Calls the dataCallback and returns its data as a QVariant.

	*/
	QVariant data() const;
};
