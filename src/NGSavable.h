// SPDX-FileCopyrightText: 2022 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#pragma once

#include <QString>
#include <KConfigGroup>

#include "nglib_export.h"

class NGLIB_EXPORT NGSavable
{
public:
	struct SaveInformation
	{
		// the name of the class responsible for restoring the state
		QString className;
		// whether or not the save was successful
		bool ok;
	};

	virtual ~NGSavable();
	virtual QUuid identifier() const = 0;
	virtual SaveInformation save(KConfigGroup& state) const = 0;
};

Q_DECLARE_INTERFACE(NGSavable, "org.kde.NGSavable/1.0");

#define NGDefineSavableMethods \
	QUuid identifier() const override; \
	SaveInformation save(KConfigGroup& state) const override;
