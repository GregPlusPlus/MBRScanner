#ifndef CLASSICGENERICMBR_H
#define CLASSICGENERICMBR_H

#include <QObject>
#include <QWidget>

#include "mbrinfowidget.h"

#include "../../propertiesplugin.h"
#include "../../PartitionWidget/partitionwidget.h"

class ClassicGenericMBR : public QObject, public PropertiesPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "soft.mbrscanner.plugins.properties.interface" FILE "")
    Q_INTERFACES(PropertiesPluginInterface)

public:
    explicit ClassicGenericMBR(QObject *parent = nullptr);
    QList<MBRTools::MBRSection> getSections();
    QWidget *getWidget(QWidget *parent = 0);
    QString getName();
    PluginStructures::PluginInfo getPluginInfo();
    void setData(const QByteArray &data);

signals:

public slots:

private:
    QByteArray m_data;

    PluginStructures::PluginInfo m_infos;

private:

};

#endif // CLASSICGENERICMBR_H
