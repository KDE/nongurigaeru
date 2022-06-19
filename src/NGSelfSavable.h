// SPDX-FileCopyrightText: 2022 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#pragma once

#include "NGRestorer.h"
#include "NGSavable.h"

#include "nglib_export.h"

class NGLIB_EXPORT NGSelfSavable : public NGRestorer, public NGSavable
{
public:
	virtual ~NGSelfSavable();
};

Q_DECLARE_INTERFACE(NGSelfSavable, "org.kde.NGSelfSavable/1.0");

#define NGDefineSelfSavableMethods \
	NGDefineRestorerMethods \
		NGDefineSavableMethods
