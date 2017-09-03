#include "plugintools.h"

void PluginTools::loadPlugins(QMap<QString, PropertiesPlugin *> &plugins, bool showProgressDialog)
{
    PluginProgressDialog dialog;

    if(showProgressDialog)
    {
        dialog.show();
    }

    QDir plugDir = QDir(qApp->applicationDirPath());
    plugDir.cd("./PropertiesPlugins");

    if(showProgressDialog)
    {
        dialog.setCount(plugDir.entryList(QDir::Files).count());
    }

    foreach(QString file, plugDir.entryList(QDir::Files))
    {
        if(file.right(4) == ".dll")
        {
            QPluginLoader loader(plugDir.absoluteFilePath(file));

            if(QObject *_plugin = loader.instance())
            {
                PropertiesPlugin* plugin = qobject_cast<PropertiesPlugin *>(_plugin);

                if(!plugins.contains(plugin->getName()))
                {
                    plugins.insert(plugin->getName(),
                                   plugin);

                    qDebug() << QObject::tr("(i) Plugin '%1' from '%2' loaded!").arg(plugin->getName()).arg(file);

                    if(showProgressDialog)
                    {
                        dialog.newPlugin(plugin);
                        dialog.update();
                        qApp->processEvents();
                    }
                }
                else
                {
                    qDebug() << QObject::tr("[!] '%1' from '%2' : A plugin  with the same key is already loaded.").arg(plugin->getName()).arg(file);
                }
            }
            else
            {
                qDebug() << QObject::tr("[!] Unable to load plugin '%1', error: %2.").arg(file).arg(loader.errorString());
            }
        }
    }

    qDebug() << QObject::tr("%1 plugins loaded in total").arg(plugins.size());
}
