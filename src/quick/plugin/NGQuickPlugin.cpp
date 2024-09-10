// SPDX-FileCopyrightText: 2022 Janet Blackquill <uhhadd@gmail.com>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#include <QQmlEngine>

#include "NGQuickPlugin.h"
#include "NGLibQuick.h"
#include "PrivateToolBarViewDelegate.h"

using namespace Qt::Literals::StringLiterals;

void NGQuickPlugin::registerTypes(const char *uri)
{

	qmlRegisterType<NGBeacon>(uri, 1, 0, "Beacon");
	qmlRegisterType<NGBeaconController>(uri, 1, 0, "BeaconController");
	qmlRegisterUncreatableType<NGBeaconControllerDelegate>(uri, 1, 0, "BeaconControllerDelegate", u"BeaconControllerDelegate is an abstract interface. You should implement this from C++, and then pass it to QML."_s);
	qmlRegisterUncreatableType<NGToolBarController>(uri, 1, 0, "ToolBarController", u"ToolBarControllers should be created in C++, and then passed to QML."_s);
	qmlRegisterType<PrivateToolBarViewDelegate>("Nongurigaeru.Private", 1, 0, "PrivateToolBarViewDelegate");
}
