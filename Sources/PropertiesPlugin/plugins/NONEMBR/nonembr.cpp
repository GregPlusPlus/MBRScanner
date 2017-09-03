#include "nonembr.h"

NONEMBR::NONEMBR(QObject *parent) : QObject(parent), PropertiesPluginInterface()
{

}

QList<MBRTools::MBRSection> NONEMBR::getSections()
{
    return QList<MBRTools::MBRSection>();
}

QWidget *NONEMBR::getWidget(QWidget *parent)
{
    return new QWidget(parent);
}

QString NONEMBR::getName()
{
    return "NONE";
}

PluginStructures::PluginInfo NONEMBR::getPluginInfo()
{
    PluginStructures::PluginInfo infos;
    infos.key = "NONE";
    infos.description = "Plugin for 'Modern Standard MBR'.";
    infos.author = "MBRScanner Default Pack";
    infos.version = "1.0";

    return infos;
}

void NONEMBR::setData(const QByteArray &data)
{
    Q_UNUSED(data)
}
