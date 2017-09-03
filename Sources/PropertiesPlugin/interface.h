#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QString>
#include <QList>
#include <QByteArray>

#include "../Core/mbrtools.h"
#include "pluginstructures.h"

class PropertiesPluginInterface
{
public:
    virtual ~PropertiesPluginInterface() {}
    virtual QList<MBRTools::MBRSection> getSections() = 0;
    virtual QWidget* getWidget(QWidget *parent = 0) = 0;
    virtual QString getName() = 0;
    virtual PluginStructures::PluginInfo getPluginInfo() = 0;
    virtual void setData(const QByteArray &data) = 0;
};

typedef PropertiesPluginInterface PropertiesPlugin;

Q_DECLARE_INTERFACE(PropertiesPluginInterface, "soft.mbrscanner.plugins.properties.interface")
#endif // INTERFACE_H
