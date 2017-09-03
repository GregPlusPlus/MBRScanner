#include "modernstandardmbr.h"

ModernStandardMBR::ModernStandardMBR(QObject *parent) : QObject(parent), PropertiesPluginInterface()
{
    m_infos.key = "Modern Standard MBR";
    m_infos.description = "Plugin for 'Modern Standard MBR'.";
    m_infos.author = "MBRScanner Default Pack";
    m_infos.version = "1.0";
}

QList<MBRTools::MBRSection> ModernStandardMBR::getSections()
{
    MBRTools::MBRSection bootstrapSection1 = {
        0x000,
        218,
        "Bootstrap code area 1",
        QColor(255, 128, 255)
    };

    MBRTools::MBRSection diskTimestampSection = {
        0x0DA,
        6,
        "Disk timestamp",
        QColor(153, 255, 153)
    };

    MBRTools::MBRSection bootstrapSection2 = {
        0x0E0,
        216,
        "Bootstrap code area 2",
        QColor(255, 128, 255)
    };

    MBRTools::MBRSection diskSignatureSection = {
        0x1B8,
        6,
        "Disk signature",
        QColor(204, 204, 255)
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

    sections                <<
    bootstrapSection1       <<
    diskTimestampSection    <<
    bootstrapSection2       <<
    diskSignatureSection    <<
    partitionEntry1         <<
    partitionEntry2         <<
    partitionEntry3         <<
    partitionEntry4         <<
    bootSignatureSection;

    return sections;
}

QWidget *ModernStandardMBR::getWidget(QWidget *parent)
{
    MBRInfoWidget *w = new MBRInfoWidget(parent);
    w->setMBRType(m_infos.key);

    w->setData(&m_data);

    return w;
}

QString ModernStandardMBR::getName()
{
    return m_infos.key;
}

PluginStructures::PluginInfo ModernStandardMBR::getPluginInfo()
{
    return m_infos;
}

void ModernStandardMBR::setData(const QByteArray &data)
{
    m_data = data;
}
