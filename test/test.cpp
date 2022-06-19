// SPDX-FileCopyrightText: 2022 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#include <KSharedConfig>
#include <QTest>

#include "NGPrivateConstants_p.h"
#include "NGRestorer.h"
#include "NGSelfSavable.h"
#include "NGPropertySavingRestoring.h"

class SimpleObject : public QObject, public NGSelfSavable
{

	Q_OBJECT
	Q_INTERFACES(NGRestorer)
	Q_INTERFACES(NGSavable)
	Q_INTERFACES(NGSelfSavable)

public:
	QUuid m_id;
	QString m_foo;

	Q_INVOKABLE SimpleObject() : QObject(), NGSelfSavable() { }
	void restore(QUuid id, const KConfigGroup& state, CompletionHandler completionHandler) override
	{
		auto ret = new SimpleObject;
		ret->m_id = id;
		ret->m_foo = state.readEntry("foo");
		completionHandler(ret);
	}
	QUuid identifier() const override
	{
		return m_id;
	}
	SaveInformation save(KConfigGroup& state) const override
	{
		state.writeEntry("foo", m_foo);
		return SaveInformation{.className = "SimpleObject*", .ok = true};
	}
};

class AutoObject : public QObject, public NGSelfSavable
{

	Q_OBJECT
	Q_INTERFACES(NGRestorer)
	Q_INTERFACES(NGSavable)
	Q_INTERFACES(NGSelfSavable)

public:
	QUuid m_id;
	SimpleObject* m_foo = nullptr;
	int m_wu = 0;
	Q_PROPERTY(SimpleObject* foo MEMBER m_foo)
	Q_PROPERTY(int wu MEMBER m_wu)

	Q_INVOKABLE AutoObject() : QObject(), NGSelfSavable() { }
	void restore(QUuid id, const KConfigGroup& state, CompletionHandler completionHandler) override
	{
		auto ret = new AutoObject;
		ret->m_id = id;
		NGPropertySavingRestoring::restoreProperties(state, ret);
		completionHandler(ret);
	}
	QUuid identifier() const override
	{
		return m_id;
	}
	SaveInformation save(KConfigGroup& state) const override
	{
		NGPropertySavingRestoring::saveProperties(state, this);
		return SaveInformation{.className = "AutoObject*", .ok = true};
	}
};

static NGMetaTypeRegisterer<SimpleObject*> simpleRegisterer;
static NGMetaTypeRegisterer<AutoObject*> autoRegisterer;

class Test : public QObject
{
	Q_OBJECT

private Q_SLOTS:
	void testSimple()
	{
		auto test = KSharedConfig::openConfig("nglibtest");

		auto grp = test->group("simple");
		{
			auto object = new SimpleObject;
			object->m_foo = "wawajete";
			saveSavable(grp, object);
		}
		test->sync();
		{
			auto restorer = getRestorer(grp.group(QUuid().toString(QUuid::WithoutBraces)));
			QVERIFY(restorer);
			restorer->restore(QUuid(), grp.group(QUuid().toString(QUuid::WithoutBraces)), [](QObject* obj) {
				QVERIFY(obj);
				auto loaded = qobject_cast<SimpleObject*>(obj);
				QVERIFY(loaded);
				QCOMPARE(loaded->m_foo, "wawajete");
			});
		}
	}
	void testAuto()
	{
		auto test = KSharedConfig::openConfig("nglibtest");

		auto grp = test->group("auto");
		{
			auto object = new AutoObject;
			object->m_foo = new SimpleObject;
			object->m_foo->m_foo = "wawajete";
			object->m_wu = 50;
			saveSavable(grp, object);
		}
		test->sync();
		{
			auto restorer = getRestorer(grp.group(QUuid().toString(QUuid::WithoutBraces)));
			restorer->restore(QUuid(), grp.group(QUuid().toString(QUuid::WithoutBraces)), [](QObject* obj) {
				QVERIFY(obj);
				auto loaded = qobject_cast<AutoObject*>(obj);
				QVERIFY(loaded);
				QVERIFY(loaded->m_foo);
				QCOMPARE(loaded->m_wu, 50);
				QCOMPARE(loaded->m_foo->m_foo, "wawajete");
			});
		}
	}
};

QTEST_MAIN(Test)

#include "test.moc"
