// SPDX-FileCopyrightText: 2022 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#pragma once

#include <QObject>

#include "NGToolBarItem.h"

#include "nglibquick_export.h"

class NGToolBarDelegate;

/**

<summary>

Controller object for which items appear in a toolbar, in what order, what items could appear in one, and its saving.

</summary>

An NGToolBarController controls one or more toolbar views that can read its properties.
Items that display a toolbar and its possible items are available from Nongurigaeru's quick plugin (see ToolBarView and ToolBarPaletteView), and are generally what you should use to display the items of an NGToolBarController.
However, implementing your own view for an NGToolBarController is possible if the stock ones do not suffice.

NGToolBarController objects have a non-unique identifier possibly shared with other NGToolBarController instances, to identify what toolbar they control.
A recommended naming scheme for identifiers is to name them after their place in the application's UI, and to make them something user readable for if users choose to edit the config manually.
Examples: <c>"Main"</c>, <c>"EmailComposer"</c>, <c>"Sidebar"</c>.

All toolbars with the same identifier will share the same items, initialised from the NGToolBarDelegate provided to the first toolbar constructed with a given identifier.
If all toolbars with a given identifier are destructed, the shared data will be reset, and the next toolbar to be created with the same identifier will re-initialise the data from its NGToolBarDelegate.

NGToolBarController automatically saves and loads the user's configured current set of toolbar items.

*/
class NGLIBQUICK_EXPORT NGToolBarController final : public QObject
{

	Q_OBJECT

	struct Private;
	QScopedPointer<Private> d;

public:
	explicit NGToolBarController(const QString& identifier, NGToolBarDelegate* delegate, QObject* outlet, QObject* parent = nullptr);
	~NGToolBarController();

	/**

	The items currently configured to be in the toolbar.

	*/
	Q_PROPERTY(QList<NGToolBarItem> items READ items NOTIFY itemsChanged)
	QList<NGToolBarItem> items() const;
	Q_SIGNAL void itemsChanged();

	/**

	The items that can be added to the toolbar.

	*/
	Q_PROPERTY(QList<NGToolBarItem> possibleItems READ possibleItems CONSTANT)
	QList<NGToolBarItem> possibleItems() const;

	/**

	The items that are in the toolbar if there is no configuration for it yet.

	*/
	Q_PROPERTY(QList<NGToolBarItem> defaultItems READ defaultItems CONSTANT)
	QList<NGToolBarItem> defaultItems() const;

	/**

	Items instantiated by toolbar views should have this object assigned to their "outlet" property.
	Any app-provided object can go here, and should be used by end-user toolbar item components to communicate with the containing application.

	*/
	Q_PROPERTY(QObject* outlet READ outlet WRITE setOutlet NOTIFY outletChanged)
	QObject* outlet() const;
	void setOutlet(QObject* outlet);
	Q_SIGNAL void outletChanged();

	/**

	Removes the item located at the given index.

	*/
	Q_INVOKABLE void removeItemAt(int index);

	/**

	Appends the item with the given identifier to the toolbar's current items, sourced from its possibleItems.

	*/
	Q_INVOKABLE void appendItem(const QString& id);

	/**

	Prepends the item with the given identifier before the given index, sourced from its possibleItems.

	*/
	Q_INVOKABLE void addItemBefore(const QString& id, int index);

	/**

	Appends the item with the given identifier after the given index, sourced from its possibleItems.

	*/
	Q_INVOKABLE void addItemAfter(const QString& id, int index);

	/**

	Resets the toolbar's items to its list of defaultItems.

	*/
	Q_INVOKABLE void resetToolbar();
};
