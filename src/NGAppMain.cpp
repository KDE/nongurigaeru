#include <KConfigGui>
#include <KLocalizedString>
#include <KConfig>
#include <KSharedConfig>

#include <QApplication>
#include <QDebug>
#include <QMetaType>
#include <QSemaphore>
#include <QSessionManager>

#include "NGAppMain.h"
#include "NGApplication.h"
#include "NGPrivateConstants_p.h"
#include "NGRestorer.h"

int NGAppMain(int* argc, char*** argv, const NGAppData& data)
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

	KLocalizedString::setApplicationDomain(data.translationDomain);

	NGApplication app(*argc, *argv);
	app.setDesktopFileName(data.desktopFile);

	// TODO: global setting for remembering state
	if (true) {
		auto nglibRestorationGroup = app.isSessionRestored()
			? sessionRestorationConfig()->group(nglibRestorationKey)
			: KSharedConfig::openConfig()->group(nglibRestorationKey);

		const auto hasRestorables = nglibRestorationGroup.groupList().length() > 0;

		if (hasRestorables) {
			QSemaphore sem(nglibRestorationGroup.groupList().length());
			for (const auto& key : nglibRestorationGroup.groupList()) {
				auto subgroup = nglibRestorationGroup.group(key);
				auto restorationClass = subgroup.readEntry<QString>(nglibRestorationClassKey, "");
				auto type = QMetaType::type(restorationClass.toStdString().c_str());

				if (type == QMetaType::UnknownType) {
					qWarning() << "Unknown restoration class" << restorationClass;
					sem.release();
					continue;
				}

				NGRestorer* restorer = qobject_cast<NGRestorer*>(QMetaType::metaObjectForType(type)->newInstance());

				sem.acquire();
				restorer->restore(QUuid::fromString(key), subgroup, [&sem, restorer](NGSavable*) {
					sem.release();

					restorer->deleteLater();
				});
			}
			sem.acquire();
		}
	}

	if (data.initialisedCallback != nullptr) {
		data.initialisedCallback();
	}

	return app.exec();
}
