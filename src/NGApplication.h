// SPDX-FileCopyrightText: 2022 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#pragma once

#include <QApplication>
#include <QObject>

#include <KConfigGroup>

#include "nglib_export.h"

#define NGApplicationSuperclass QApplication

class NGSavable;

class NGLIB_EXPORT NGApplication final : public NGApplicationSuperclass
{
	Q_OBJECT

	struct Private;
	QScopedPointer<Private> d;

	void saveSavables(KConfigGroup& group);
	void saveSavablesConfig();
	void saveSavablesSession(QSessionManager& manager);

public:
	NGApplication(int& argc, char** argv);
	~NGApplication();

	void registerSavable(NGSavable* savable);
	void unregisterSavable(NGSavable* savable);
};

#ifdef qApp
#undef qApp
#define qApp qobject_cast<NGApplication*>(QCoreApplication::instance())
#endif
