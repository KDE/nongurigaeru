// SPDX-FileCopyrightText: 2022 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#pragma once

#include <QQuickItem>

#include "nglibquick_export.h"

class NGBeacon;
class NGBeaconControllerDelegate;

/**

<summary>

An item that manages a collection of key points, identified by NGBeacon items, and tells you which key point was closest when the user performs a drop operation over this item to determine what to do.

</summary>

NGBeaconController is an invisible item that accepts drop events in a drag-and-drop operation, used for various drag-and-drop tasks that rely on proximity to a key point (such as before/after a list item), rather than dropping in a rectangular area (such as inside a folder icon) to determine what to do.

One NGBeaconController manages many NGBeacon items, which are ideally situated inside it, or inside a sibling to the NGBeaconController.

NGBeacon items are used to specify key points, such as before/after a list item, or a location in a text outline or similar tree structure.
For more information on specifiying key points, see the NGBeacon documentation.

An NGBeaconController communicates with an NGBeaconControllerDelegate implementation, notifiying it of drag and drop events.
For more information on handling drag an drop events for a controller, see the NGBeaconControllerDelegate documentation.

*/
class NGLIBQUICK_EXPORT NGBeaconController : public QQuickItem
{

	Q_OBJECT

	/**

	The ID of the beacon the user is closest to during a drag and drop operation, or no beacon if there isn't a drag and drop operation or there are no beacons assigned to this NGBeaconController.

	*/
	Q_PROPERTY(QString activeBeaconID READ activeBeaconID NOTIFY activeBeaconIDChanged)

	/**

	The delegate that this item will notify of drag and drop events.

	*/
	Q_PROPERTY(NGBeaconControllerDelegate* delegate READ delegate WRITE setDelegate NOTIFY delegateChanged)

	struct Private;
	QScopedPointer<Private> d;

	friend class NGBeacon;

	void addBeacon(NGBeacon* beacon);
	void delBeacon(NGBeacon* beacon);
	void computeActiveBeacon(const QPointF& point);

protected:
	void dragEnterEvent(QDragEnterEvent*) override;
	void dragMoveEvent(QDragMoveEvent*) override;
	void dragLeaveEvent(QDragLeaveEvent*) override;
	void dropEvent(QDropEvent*) override;

public:
	explicit NGBeaconController(QQuickItem* parent = nullptr);
	~NGBeaconController();

	NGBeaconControllerDelegate* delegate() const;
	void setDelegate(NGBeaconControllerDelegate* delegate);
	Q_SIGNAL void delegateChanged();

	QString activeBeaconID() const;
	Q_SIGNAL void activeBeaconIDChanged();
};
