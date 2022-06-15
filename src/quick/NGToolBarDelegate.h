#pragma once

#include "NGToolBarItem.h"
#include "NGToolBarController.h"

#include <optional>

#include "nglibquick_export.h"

/**

<summary>

Interface that allows an NGToolBarController to communicate with an application.

</summary>

An NGToolBarDelegate subclass must be used by applications in conjunction with an NGToolBarController.
The NGToolBarController uses the NGToolBarDelegate to get application-specific items, configuration, and the QQmlEngine instance to use to instantiate standard components.

*/
class NGLIBQUICK_EXPORT NGToolBarDelegate
{

public:
	virtual ~NGToolBarDelegate();

	/**

	The engine that will be used by the NGToolBarController to instantiate standard components.

	*/
	virtual QQmlEngine* engine() = 0;

	/**

	<param name="toolbar">A reference to the toolbar controller invoking this method.</param>

	<param name="identifier">The requested identifier. If the identifier is invalid for this delegate, it should return a null optional.</param>

	<param name="willBeInsertedIntoToolbar">Whether or not this item will be instantiated by a toolbar view. If false, it is appearing in something other than a toolbar view, such as an editor view. Applications can use this parameter to return different components for toolbar views vs. other components, such as toolbar editor views.</param>

	<returns>An NGToolBarItem for the given identifier, or a null optional if the identifier is bad.</returns>

	*/
	virtual std::optional<NGToolBarItem> itemForIdentifier(NGToolBarController* toolbar, const QString& identifier, bool willBeInsertedIntoToolbar) = 0;

	/**

	The list of possible identifiers for items in this toolbar.

	*/
	virtual QList<QString> possibleItems() = 0;

	/**

	The list of identifiers of the default set items in this toolbar.

	*/
	virtual QList<QString> defaultitems() = 0;
};
