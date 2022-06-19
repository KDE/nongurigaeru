// SPDX-FileCopyrightText: 2022 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#include <QMimeData>

#include "NGBeacon.h"
#include "PrivateToolBarViewDelegate.h"

PrivateToolBarViewDelegate::PrivateToolBarViewDelegate(QObject* parent) : NGBeaconControllerDelegate(parent)
{

}

PrivateToolBarViewDelegate::~PrivateToolBarViewDelegate()
{

}

void PrivateToolBarViewDelegate::dragEnterEvent(QDragEnterEvent*)
{

}

void PrivateToolBarViewDelegate::dragMoveEvent(QDragMoveEvent*)
{

}

void PrivateToolBarViewDelegate::dragLeaveEvent(QDragLeaveEvent*)
{

}

void PrivateToolBarViewDelegate::dropEvent(NGBeacon* beacon, QDropEvent* event)
{
	if (beacon == nullptr)
		return;

	auto data = beacon->data();
	auto list = data.toList();
	auto index = list[1].toInt();
	auto before = list[0].toString() == "before";
	auto kind = QString::fromUtf8(event->mimeData()->data("application/x-nongurigaeru-toolbar-item"));
	auto isDefault = QString::fromUtf8(event->mimeData()->data("application/x-nongurigaeru-toolbar-default-set")) == "yes";

	if (isDefault) {
		controller->resetToolbar();
	} else if (before) {
		controller->addItemBefore(kind, index);
	} else {
		controller->addItemAfter(kind, index);
	}
}
