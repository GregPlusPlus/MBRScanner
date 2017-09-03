#ifndef PLUGINTOOLS_H
#define PLUGINTOOLS_H

#include <QApplication>
#include <QObject>
#include <QDir>
#include <QMap>
#include <QPluginLoader>

#include <QDebug>

#include "PropertiesPlugin/propertiesplugin.h"
#include "GUI/pluginprogressdialog.h"

namespace PluginTools
{
    void loadPlugins(QMap<QString, PropertiesPlugin*> &plugins, bool showProgressDialog);
}

#endif // PLUGINTOOLS_H
