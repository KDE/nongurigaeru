// SPDX-FileCopyrightText: 2022 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#pragma once

#include <QApplication>
#include <QString>

#include <KAboutData>
#include <KConfigGroup>

#include <functional>

#include "nglib_export.h"

struct NGAppData final
{
	const char* translationDomain;
	QString desktopFile;
	KAboutData aboutData;
	std::function<void()> initialisedCallback;
};

int NGLIB_EXPORT NGAppMain(int* argc, char*** argv, const NGAppData& = NGAppData());
