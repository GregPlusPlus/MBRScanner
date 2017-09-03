#ifndef CLASSICGENERICMBR_H
#define CLASSICGENERICMBR_H

#include <QObject>
#include <QWidget>

#include "../../propertiesplugin.h"
#include "mbrinfowidget.h"

class ModernStandardMBR : public QObject, public PropertiesPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "soft.mbrscanner.plugins.properties.interface" FILE "")
    Q_INTERFACES(PropertiesPluginInterface)

public:
    explicit ModernStandardMBR(QObject *parent = nullptr);
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
};

#endif // CLASSICGENERICMBR_H
