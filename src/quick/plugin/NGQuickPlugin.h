#pragma once

#include <QQmlExtensionPlugin>

class NGQuickPlugin : public QQmlExtensionPlugin
{

	Q_OBJECT
	Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
	void registerTypes(const char* uri) override;

private:
	QUrl resolveFileURL(const QString& path) const
	{
		return baseUrl().toString() + QLatin1Char('/') + path;
	}
};
