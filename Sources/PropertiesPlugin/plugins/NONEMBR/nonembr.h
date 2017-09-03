#ifndef NONEMBR_H
#define NONEMBR_H

#include "../../propertiesplugin.h"

class NONEMBR : public QObject, public PropertiesPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "soft.mbrscanner.plugins.properties.interface" FILE "")
    Q_INTERFACES(PropertiesPluginInterface)

public:
    explicit NONEMBR(QObject *parent = nullptr);
    QList<MBRTools::MBRSection> getSections();
    QWidget* getWidget(QWidget *parent = 0);
    QString getName();
    PluginStructures::PluginInfo getPluginInfo();
    void setData(const QByteArray &data);

private:
};

#endif // NONEMBR_H
