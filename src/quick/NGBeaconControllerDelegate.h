// SPDX-FileCopyrightText: 2022 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#pragma once

#include <QQuickItem>

#include "nglibquick_export.h"

class NGBeacon;

/**

An object that an NGBeaconController notifies of drag and drop events.

*/
class NGLIBQUICK_EXPORT NGBeaconControllerDelegate : public QObject
{
	Q_OBJECT

public:
	explicit NGBeaconControllerDelegate(QObject* parent = nullptr);
	virtual ~NGBeaconControllerDelegate();

	/**

	Implement this method to be notified when the NGBeaconController receives a dragEnterEvent.

	*/
	virtual void dragEnterEvent(QDragEnterEvent*){};
	/**

	Implement this method to be notified when the NGBeaconController receives a dragMoveEvent.

	*/
	virtual void dragMoveEvent(QDragMoveEvent*){};
	/**

	Implement this method to be notified when the NGBeaconController receives a dragLeaveEvent.

	*/
	virtual void dragLeaveEvent(QDragLeaveEvent*){};
	/**

	Implement this method to be notified when the NGBeaconController receives a dropEvent, as well as
	to receive the closest beacon to the drop point.

	*/
	virtual void dropEvent(NGBeacon*, QDropEvent*){};
};
