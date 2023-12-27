// SPDX-FileCopyrightText: 2022 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#include <QMimeData>

#include "NGBeacon.h"
#include "PrivateToolBarViewDelegate.h"

using namespace Qt::Literals::StringLiterals;

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
	auto before = list[0].toString() == u"before"_s;
	auto kind = QString::fromUtf8(event->mimeData()->data(u"application/x-nongurigaeru-toolbar-item"_s));
	auto isDefault = QString::fromUtf8(event->mimeData()->data(u"application/x-nongurigaeru-toolbar-default-set"_s)) == u"yes"_s;

	if (isDefault) {
		controller->resetToolbar();
	} else if (before) {
		controller->addItemBefore(kind, index);
	} else {
		controller->addItemAfter(kind, index);
	}
}
