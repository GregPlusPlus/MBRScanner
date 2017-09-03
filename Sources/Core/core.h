#ifndef CORE_H
#define CORE_H

#include <QObject>

#include <QWidget>
#include <QScrollArea>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>

#include <QDataStream>
#include <QString>
#include <QByteArray>
#include <QMap>

#include <QDebug>

#include <qhexedit.h>

#include "GUI/driveselectiondialog.h"
#include "GUI/pluginsselectiondialog.h"
#include "GUI/legenddialog.h"

#include "hexdisplay.h"

#include "PropertiesPlugin/propertiesplugin.h"

namespace Core
{
    bool loadMBR(QWidget *parent,
            PropertiesPlugin **currentPlugin,
            QMap<QString, PropertiesPlugin*> plugins,
            LegendDialog *legendDialog,
            QByteArray *data,
            QHexEdit *hexEdit,
            QHexDocument *hexDoc,
            QWidget **w,
            QScrollArea *scroll);

    bool loadMBRFromFile(QWidget *parent,
                         PropertiesPlugin **currentPlugin,
                         QMap<QString, PropertiesPlugin*> plugins,
                         LegendDialog *legendDialog,
                         QByteArray *_data,
                         QHexEdit *hexEdit,
                         QHexDocument *hexDoc,
                         QWidget **w,
                         QScrollArea *scroll);

    void updatePropertiesWidget(PropertiesPlugin *currentPlugin, QWidget **w, QScrollArea *scroll);

    bool saveMBR(QWidget *parent, QByteArray *data);
}

#endif // CORE_H
