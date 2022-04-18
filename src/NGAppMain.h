#pragma once

#include <QApplication>
#include <QString>

#include <KAboutData>
#include <KConfigGroup>

#include <functional>

#include "nglib_export.h"

struct NGAppData
{
	const char* translationDomain;
	QString desktopFile;
	KAboutData aboutData;
	std::function<void()> initialisedCallback;
};

int NGLIB_EXPORT NGAppMain(int* argc, char*** argv, const NGAppData& = NGAppData());
