#include "NGRestorer.h"
#include "NGToolBarDelegate.h"
#include "NGToolBarController.h"
#include "NGPrivateConstants_p.h"

struct NGToolBarInformation
{
	QList<NGToolBarItem> items;
	QList<NGToolBarItem> possibleItems;
	QList<NGToolBarItem> defaultItems;

	QList<NGToolBarController*> toolbars;
};

struct NGToolBarController::Private
{
	NGToolBarController* q;
	NGToolBarDelegate* delegate;
	QObject* outlet;
	QString identifier;

	static QMap<QString, NGToolBarInformation> information;
	void initInfo();
	void save();
	void notify()
	{
		for (auto* toolbar : info().toolbars) {
			Q_EMIT toolbar->itemsChanged();
		}
	}
	std::optional<NGToolBarItem> item(const QString& name, bool inToolbar)
	{
		return delegate->itemForIdentifier(q, name, inToolbar);
	}
	NGToolBarInformation& info()
	{
		if (!information.contains(identifier)) {
			initInfo();
		}
		return information[identifier];
	}
};

QMap<QString, NGToolBarInformation> NGToolBarController::Private::information;

void NGToolBarController::Private::initInfo()
{
	NGToolBarInformation info;
	info.toolbars << q;
	for (const auto& item : delegate->possibleItems()) {
		info.possibleItems << *delegate->itemForIdentifier(q, item, false);
	}
	for (const auto& item : delegate->defaultitems()) {
		info.defaultItems << *delegate->itemForIdentifier(q, item, false);
	}

	auto config = preferencesConfig();
	auto toolbar = config->group("Nongurigaeru").group("Toolbars").group(identifier);

	if (!toolbar.hasKey("Items")) {
		toolbar.writeEntry("Items", delegate->defaultitems());
	}
	const auto items = toolbar.readEntry<QStringList>("Items", QStringList());

	for (const auto& item : items) {
		if (auto it = delegate->itemForIdentifier(q, item, true)) {
			info.items << *it;
		}
	}

	information[identifier] = info;
}

void NGToolBarController::Private::save()
{
	auto config = preferencesConfig();
	auto toolbar = config->group("Nongurigaeru").group("Toolbars").group(identifier);
	QStringList items;

	for (const auto& item : info().items) {
		items << item.identifier();
	}

	toolbar.writeEntry("Items", items);
}

NGToolBarController::NGToolBarController(const QString& identifier, NGToolBarDelegate* delegate, QObject* outlet, QObject* parent)
	: QObject(parent)
	, d(new Private{ this, delegate, outlet, identifier })
{
}

NGToolBarController::~NGToolBarController()
{
	d->info().toolbars.removeAll(this);
	if (d->info().toolbars.isEmpty()) {
		d->information.remove(d->identifier);
	}
}

QList<NGToolBarItem> NGToolBarController::items() const
{
	return d->info().items;
}

QList<NGToolBarItem> NGToolBarController::possibleItems() const
{
	return d->info().possibleItems;
}

QList<NGToolBarItem> NGToolBarController::defaultItems() const
{
	return d->info().defaultItems;
}

void NGToolBarController::removeItemAt(int index)
{
	d->info().items.removeAt(index);
	d->notify();
	d->save();
}

void NGToolBarController::appendItem(const QString& id)
{
	auto item = *d->item(id, true);
	d->info().items << item;
	d->notify();
	d->save();
}

void NGToolBarController::addItemBefore(const QString& id, int index)
{
	auto item = *d->item(id, true);
	d->info().items.insert(index, item);
	d->notify();
	d->save();
}

void NGToolBarController::addItemAfter(const QString& id, int index)
{
	auto item = *d->item(id, true);
	d->info().items.insert(index+1, item);
	d->notify();
	d->save();
}

void NGToolBarController::resetToolbar()
{
	QList<NGToolBarItem> items;
	for (const auto& item : d->info().defaultItems) {
		items << *d->item(item.identifier(), true);
	}
	d->info().items = items;
	d->notify();
	d->save();
}

QObject* NGToolBarController::outlet() const
{
	return d->outlet;
}

void NGToolBarController::setOutlet(QObject* outlet)
{
	if (d->outlet != outlet)
		return;

	d->outlet = outlet;
	Q_EMIT outletChanged();
}

