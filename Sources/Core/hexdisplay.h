#ifndef HEXDISPLAY_H
#define HEXDISPLAY_H

#include <QString>
#include <QColor>
#include <QList>

#include <QByteArray>

#include <qhexedit.h>

#include "Core/mbrtools.h"
#include "PropertiesPlugin/propertiesplugin.h"

namespace HexDisplay {
    void displaySections(QHexDocument *doc, PropertiesPlugin *plugin);
    void displaySection(QHexDocument *doc, MBRTools::MBRSection section);
    bool loadMBR(QString path, QByteArray *data, QHexEdit *edit, QHexDocument *doc, PropertiesPlugin *plugin);
}

#endif // HEXDISPLAY_H
