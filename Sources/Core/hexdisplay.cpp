#include "hexdisplay.h"


void HexDisplay::displaySection(QHexDocument *doc, MBRTools::MBRSection section)
{
    doc->highlightBackRange(section.startByte, section.length, section.color);
    doc->commentRange(section.startByte, section.length, section.name);
}

void HexDisplay::displaySections(QHexDocument *doc, PropertiesPlugin *plugin)
{
    for(int i = 0 ; i < plugin->getSections().length() ; i++)
    {
        displaySection(doc, plugin->getSections().at(i));
    }
}

bool HexDisplay::loadMBR(QString path, QByteArray *data, QHexEdit *edit, QHexDocument *doc, PropertiesPlugin *plugin)
{
    //"\\\\.\\C:"
    //"\\\\.\\PhysicalDrive0"

    char *buff = new char[512];
    if(MBRTools::readDisk(path, buff, 0, 512))
    {
        return 0;
    }

    data->setRawData(buff, 512);

    doc = QHexDocument::fromMemory(*data);
    edit->setDocument(doc);

    if(plugin)
    {
        HexDisplay::displaySections(doc, plugin);

        plugin->setData(*data);
    }

    return 1;
}
