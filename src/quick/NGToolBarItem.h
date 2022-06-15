#pragma once

#include <QObject>
#include <QQmlEngine>

#include "nglibquick_export.h"

/**

<summary>

An object containing metadata about a toolbar item, and the QQmlComponent to instantiate.

</summary>

*/
struct NGLIBQUICK_EXPORT NGToolBarItem final
{

	Q_GADGET

	struct Private;
	QSharedDataPointer<Private> d;

public:
	/**

	The identifier of this item.

	*/
	Q_PROPERTY(QString identifier READ identifier)
	QString identifier() const;

	/**

	The user-visible label of this item, displayed in views such as a toolbar editor view.

	*/
	Q_PROPERTY(QString label READ label WRITE setLabel)
	QString label() const;
	void setLabel(const QString& label);

	/**

	The component to be instantiated by views rendering this component.
	This component should have a property named "outlet", which views will assign the specified object to.

	<seealso cref="NGToolBarController::outlet">

	*/
	Q_PROPERTY(QQmlComponent* component READ component WRITE setComponent)
	QQmlComponent* component() const;
	void setComponent(QQmlComponent* component);

	explicit NGToolBarItem(const QString& identifier, const QString& label, QQmlComponent* component);
	explicit NGToolBarItem();
	NGToolBarItem(const NGToolBarItem& other);
	NGToolBarItem& operator=(const NGToolBarItem& other);
	~NGToolBarItem();
};

Q_DECLARE_METATYPE(NGToolBarItem)
Q_DECLARE_METATYPE(QList<NGToolBarItem>)
