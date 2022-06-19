// SPDX-FileCopyrightText: 2022 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#include <QQmlEngine>

#include "NGQuickPlugin.h"
#include "NGLibQuick.h"
#include "PrivateToolBarViewDelegate.h"

void NGQuickPlugin::registerTypes(const char *uri)
{

	qmlRegisterType<NGBeacon>(uri, 1, 0, "Beacon");
	qmlRegisterType<NGBeaconController>(uri, 1, 0, "BeaconController");
	qmlRegisterUncreatableType<NGBeaconControllerDelegate>(uri, 1, 0, "BeaconControllerDelegate", "BeaconControllerDelegate is an abstract interface. You should implement this from C++, and then pass it to QML.");
	qmlRegisterUncreatableType<NGToolBarController>(uri, 1, 0, "ToolBarController", "ToolBarControllers should be created in C++, and then passed to QML.");
	qmlRegisterType(resolveFileURL("ToolBarView.qml"), uri, 1, 0, "ToolBarView");
	qmlRegisterType(resolveFileURL("ToolBarPaletteView.qml"), uri, 1, 0, "ToolBarPaletteView");
	qmlRegisterType(resolveFileURL("BlockMouseArea.qml"), uri, 1, 0, "BlockMouseArea");
	qmlRegisterType(resolveFileURL("BlockDropArea.qml"), uri, 1, 0, "BlockDropArea");
	qmlRegisterType<PrivateToolBarViewDelegate>("Nongurigaeru.Private", 1, 0, "PrivateToolBarViewDelegate");

}
