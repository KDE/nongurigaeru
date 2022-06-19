// SPDX-FileCopyrightText: 2022 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#pragma once

#include "NGBeaconControllerDelegate.h"
#include "NGToolBarController.h"

class PrivateToolBarViewDelegate : public NGBeaconControllerDelegate
{
	Q_OBJECT

public:
	explicit PrivateToolBarViewDelegate(QObject* parent = nullptr);
	~PrivateToolBarViewDelegate();

	void dragEnterEvent(QDragEnterEvent*) override;
	void dragMoveEvent(QDragMoveEvent*) override;
	void dragLeaveEvent(QDragLeaveEvent*) override;
	void dropEvent(NGBeacon*, QDropEvent*) override;

	Q_PROPERTY(NGToolBarController* controller MEMBER controller NOTIFY controllerChanged REQUIRED)
	NGToolBarController* controller = nullptr;
	Q_SIGNAL void controllerChanged();
};
