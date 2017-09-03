#include "core.h"

bool Core::loadMBR(QWidget *parent,
                   PropertiesPlugin **currentPlugin,
                   QMap<QString, PropertiesPlugin *> plugins,
                   LegendDialog *legendDialog,
                   QByteArray *data, QHexEdit *hexEdit,
                   QHexDocument *hexDoc, QWidget **w,
                   QScrollArea *scroll)
{
    QString path = DriveSelectionDialog::selectDrive();

    (*currentPlugin) = PluginsSelectionDialog::selectPlugin(plugins);
    legendDialog->setPlugin(*currentPlugin);

    if(HexDisplay::loadMBR(path, data, hexEdit, hexDoc, *currentPlugin))
    {
        updatePropertiesWidget(*currentPlugin, w, scroll);
    }
    else
    {
        QMessageBox::information(parent, QObject::tr("Unable to read the MBR."),
                                 QObject::tr("Unable to read the MBR at '%1'.<br>Please, try to run this program as administrator.").arg(path));

        return 0;
    }

    return 1;
}

bool Core::loadMBRFromFile(QWidget *parent,
                           PropertiesPlugin **currentPlugin,
                           QMap<QString, PropertiesPlugin *> plugins,
                           LegendDialog *legendDialog,
                           QByteArray *_data,
                           QHexEdit *hexEdit,
                           QHexDocument *hexDoc,
                           QWidget **w,
                           QScrollArea *scroll)
{
    QString fileName = QFileDialog::getOpenFileName(parent, QObject::tr("Select a file"), QString(),
                                                    QObject::tr("Binary files (*.bin *.dat *.mbr);;All files (*.*)"));

    if(fileName.isEmpty())return 0;

    (*currentPlugin) = PluginsSelectionDialog::selectPlugin(plugins);
    legendDialog->setPlugin(*currentPlugin);

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();

        if(data.length() > 512)
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(parent, QObject::tr("File too big"),
                                          QObject::tr("The selected file is larger than 512 bytes.<br>"
                                                      "It may not represent a valid MBR,<br>"
                                                      "if this file represents a whole drive, look at the first 512 bytes.<br><br>"
                                                      "Do your really want to load this file?"),
                                          QMessageBox::Yes|QMessageBox::No);

            if(reply != QMessageBox::Yes)return 0;
        }
        else if(data.length() < 512)
        {
            QMessageBox::warning(parent, QObject::tr("File too short"),
                                 QObject::tr("The selected file is smaller than 512 bytes.<br>"
                                             "<strong>MBR Scanner</strong> and plugins can't read a file smaller than 512 bytes."));

            return 0;
        }

        _data->clear();

        (*_data) = data;

        hexDoc = QHexDocument::fromMemory(*_data);
        hexEdit->setDocument(hexDoc);

        if(*currentPlugin)
        {
            HexDisplay::displaySections(hexDoc, *currentPlugin);

            (*currentPlugin)->setData(*_data);

            updatePropertiesWidget(*currentPlugin, w, scroll);
        }
    }
    else
    {
        QMessageBox::information(parent, QObject::tr("Unable to read the file."),
                                 QObject::tr("Unable to read the file at '%1'.<br>Error: %2").arg(fileName).arg(file.errorString()));

        return 0;
    }

    return 1;
}

void Core::updatePropertiesWidget(PropertiesPlugin *currentPlugin, QWidget **w, QScrollArea *scroll)
{
    if(currentPlugin)
    {
        delete (*w);

        (*w) = currentPlugin->getWidget(scroll);

        scroll->setWidget(*w);
    }
}

bool Core::saveMBR(QWidget *parent, QByteArray *data)
{
    if(data->isEmpty()) return 0;

    QString fileName = QFileDialog::getSaveFileName(parent, QObject::tr("Save MBR"), QString(), QObject::tr("Binary files (*.mbr);;"
                                                                                                            "Binary files (*.bin);;"
                                                                                                            "Binary files (*.dat)"));
    if(fileName.isEmpty())return 0;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(parent, QObject::tr("Unable to open the file."),
                                 QObject::tr("Unable to open the file at '%1'.<br>Error: %2").arg(fileName).arg(file.errorString()));
        return 0;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_8);
    out.writeRawData(data->data(), data->length());

    return 1;
}
