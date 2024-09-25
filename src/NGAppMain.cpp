// SPDX-FileCopyrightText: 2022 Janet Blackquill <uhhadd@gmail.com>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

#include <KConfigGui>
#include <KLocalizedString>
#include <KConfig>
#include <KSharedConfig>
#include <KDBusService>

#include <QApplication>
#include <QDebug>
#include <QMetaType>
#include <QSemaphore>
#include <QSessionManager>
#include <QDir>
#include <QTimer>

#include "NGAppMain.h"
#include "NGApplication.h"
#include "NGPrivateConstants_p.h"
#include "NGRestorer.h"

int NGAppMain(int* argc, char*** argv, const NGAppData& data)
{
	KLocalizedString::setApplicationDomain(data.translationDomain);

	NGApplication app(*argc, *argv);
	app.setDesktopFileName(data.desktopFile);

	KDBusService service(KDBusService::Unique);

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
				auto restorer = getRestorer(subgroup);
				if (restorer == nullptr) {
					sem.release();
					continue;
				}

				sem.acquire();
				restorer->restore(QUuid::fromString(key), subgroup, [&sem, restorer](QObject*) {
					sem.release();

					delete restorer;
				});
			}
			sem.acquire();
		}
	}


	if (data.activatedCallback != nullptr) {
		if (service.isRegistered()) {
			QTimer::singleShot(0, &service, [data, &app] {
				data.activatedCallback(app.arguments(), QDir::currentPath());
			});
		}
		QObject::connect(&service, &KDBusService::activateRequested, &service, [data](const QStringList &params, const QString &cwd) {
			data.activatedCallback(params, cwd);
		});
	}

	return app.exec();
}
