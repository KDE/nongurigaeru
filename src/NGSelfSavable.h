#pragma once

#include "NGRestorer.h"
#include "NGSavable.h"

#include "nglib_export.h"

class NGLIB_EXPORT NGSelfSavable : public NGRestorer, public NGSavable
{
	virtual ~NGSelfSavable();
};

#define NGDefineSelfSavableMethods \
	NGDefineRestorerMethods \
	NGDefineSavableMethods
