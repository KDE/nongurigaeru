#pragma once

#include <KConfigGroup>

#include "NGRestorer.h"
#include "nglib_export.h"

namespace NGPropertySavingRestoring {
void NGLIB_EXPORT restoreProperties(const KConfigGroup& state, QObject* on, const QStringList& properties = {});
void NGLIB_EXPORT saveProperties(KConfigGroup& state, const QObject* from, const QStringList& properties = {});
};
