#pragma once

#include <QObject>

#include <KConfigGroup>

#include <functional>

#include "nglib_export.h"

/**

<summary>

Interface for objects that restore other objects from a serialised state

</summary>

Objects conforming to the NGRestorer interface are responsible for taking an application's serialised state and turning it back into live objects when the interface is "restored".

At restoration time, the NGApplication retrieves the restoration class from Qt's meta-object system in order to construct it.
This requires a few things:

<list>
	<item>
		The restoration class must be registered before NGAppMain is called.
		The utility class NGMetaTypeRegisterer can be used to achieve this.
	</item>
	<item>
		The restoration class must have a Q_INVOKABLE constructor with no arguments.
	</item>
	<item>
		The restoration class must declare NGRestorer as one of its Q_INTERFACES.
	</item>
</list>

*/

class NGSavable;

class NGLIB_EXPORT NGRestorer : public QObject
{
public:
	using CompletionHandler = std::function<void(NGSavable*)>;

	virtual ~NGRestorer();
	virtual void restore(QUuid id, const KConfigGroup& state, CompletionHandler completionHandler) = 0;
};

Q_DECLARE_INTERFACE(NGRestorer, "org.kde.NGRestorer/1.0");

#define NGDefineRestorerMethods \
	void restore(QUuid id, const KConfigGroup& state, CompletionHandler completionHandler) override;

template <typename T>
struct NGMetaTypeRegisterer
{
	NGMetaTypeRegisterer()
	{
		qRegisterMetaType<T>();
	}
};
