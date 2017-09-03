#ifndef MBRTOOLS_H
#define MBRTOOLS_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QColor>

#include <QDebug>

#include <windows.h>

#include <initguid.h>
#include <ntddstor.h>
#include <Setupapi.h>

#include <winioctl.h>
#include <ntddcdrm.h>
#include <Shlobj.h>

namespace MBRTools
{
    struct MBRSection{
        qint64 startByte;
        qint64 length;
        QString name;
        QColor color;
    };

    int readDisk(QString dsk,
                 char *&_buff,
                 unsigned int _nsect,
                 unsigned int _length);

    QStringList getPhysicalDisks();
    QStringList getMountedDrives();
}

#endif // MBRTOOLS_H
