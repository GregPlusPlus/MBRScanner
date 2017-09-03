#include "classicgenericmbr.h"

ClassicGenericMBR::ClassicGenericMBR(QObject *parent) : QObject(parent), PropertiesPluginInterface()
{
    m_infos.key = "Classic Generic MBR";
    m_infos.description = "Plugin for 'Classic Generic MBR'.";
    m_infos.author = "MBRScanner Default Pack";
    m_infos.version = "1.0";
}

QList<MBRTools::MBRSection> ClassicGenericMBR::getSections()
{
    MBRTools::MBRSection bootstrapSection = {
        0x000,
        446,
        "Bootstrap code area",
        QColor(255, 128, 255)
    };

    MBRTools::MBRSection partitionEntry1 = {
        0x1BE,
        16,
        "16-byte partition entry 1",
        QColor(255, 204, 102)
    };

    MBRTools::MBRSection partitionEntry2 = {
        0x1BE + 16,
        16,
        "16-byte partition entry 2",
        QColor(255, 179, 26)
    };

    MBRTools::MBRSection partitionEntry3 = {
        0x1BE + 32,
        16,
        "16-byte partition entry 3",
        QColor(255, 204, 102)
    };

    MBRTools::MBRSection partitionEntry4 = {
        0x1BE + 48,
        16,
        "16-byte partition entry 4",
        QColor(255, 179, 26)
    };

    MBRTools::MBRSection bootSignatureSection = {
        0x1FE,
        2,
        "Boot signature",
        QColor(102, 153, 255)
    };

    QList<MBRTools::MBRSection> sections;

    sections << bootstrapSection << partitionEntry1 << partitionEntry2 << partitionEntry3 << partitionEntry4 << bootSignatureSection;

    return sections;
}

QWidget *ClassicGenericMBR::getWidget(QWidget *parent)
{
    MBRInfoWidget *w = new MBRInfoWidget(parent);
    w->setMBRType(m_infos.key);

    w->setData(&m_data);

    return w;
}

QString ClassicGenericMBR::getName()
{
    return m_infos.key;
}

PluginStructures::PluginInfo ClassicGenericMBR::getPluginInfo()
{
    return m_infos;
}

void ClassicGenericMBR::setData(const QByteArray &data)
{
    m_data = data;
}
