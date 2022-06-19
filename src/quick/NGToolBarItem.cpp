// SPDX-FileCopyrightText: 2022 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#include "NGLib.h"
#include "NGToolBarItem.h"

struct NGToolBarItem::Private : public QSharedData
{
	QString identifier;
	QString label;
	QQmlComponent* component = nullptr;
};

NGToolBarItem::NGToolBarItem(const QString& identifier, const QString& label, QQmlComponent* component)
	: d(new Private)
{
	d->identifier = identifier;
	d->label = label;
	d->component = component;
}

NGToolBarItem::NGToolBarItem()
	: d(new Private)
{
}

NGToolBarItem::~NGToolBarItem()
{

}

QString NGToolBarItem::identifier() const
{
	return d->identifier;
}

QString NGToolBarItem::label() const
{
	return d->label;
}

void NGToolBarItem::setLabel(const QString& label)
{
	d->label = label;
}

QQmlComponent* NGToolBarItem::component() const
{
	return d->component;
}

void NGToolBarItem::setComponent(QQmlComponent* component)
{
	d->component = component;
}

NGToolBarItem::NGToolBarItem(const NGToolBarItem& other)
{
	d = other.d;
}

NGToolBarItem& NGToolBarItem::operator=(const NGToolBarItem& other)
{
	d = other.d;
	return *this;
}

static NGMetaTypeRegisterer<NGToolBarItem> itemRegisterer;
static NGMetaTypeRegisterer<QList<NGToolBarItem>> listRegisterer;
