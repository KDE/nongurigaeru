#include <QSessionManager>

#include <KSharedConfig>

#include "NGApplication.h"
#include "NGSavable.h"
#include "NGPrivateConstants_p.h"

struct NGApplication::Private
{
	QList<NGSavable*> savables;
};

NGApplication::NGApplication(int& argc, char** argv) : QApplication(argc, argv), d(new Private)
{
	connect(this, &QGuiApplication::saveStateRequest, this, &NGApplication::saveSavablesSession);
	connect(this, &QGuiApplication::commitDataRequest, this, &NGApplication::saveSavablesSession);
	connect(this, &QGuiApplication::aboutToQuit, this, &NGApplication::saveSavablesConfig);
}

void NGApplication::saveSavables(KConfigGroup& group)
{
	for (const auto& key : group.groupList()) {
		group.deleteGroup(key);
	}

	for (const auto* savable : d->savables) {
		auto data = saveSavable(group, savable);
		if (!data.ok) {
			// TODO: error handling
		}
	}
}

void NGApplication::saveSavablesSession(QSessionManager& manager)
{
	auto cfg = KSharedConfig::openConfig(configName(manager.sessionId(), manager.sessionKey()));
	auto group = cfg->group(nglibRestorationKey);

	saveSavables(group);
}

void NGApplication::saveSavablesConfig()
{
	auto cfg = KSharedConfig::openConfig();
	auto group = cfg->group(nglibRestorationKey);

	saveSavables(group);
}

void NGApplication::registerSavable(NGSavable* savable)
{
	d->savables << savable;
}

void NGApplication::unregisterSavable(NGSavable* savable)
{
	d->savables.removeAll(savable);
}

NGApplication::~NGApplication()
{
}
