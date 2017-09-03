#ifndef PLUGINSDIALOG_H
#define PLUGINSDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QScrollArea>
#include <QStatusBar>

#include <QIcon>

#include <QVBoxLayout>

#include <QMap>

#include "../PropertiesPlugin/propertiesplugin.h"
#include "pluginwidget.h"
#include "Tools/tools.h"

class PluginsDialog: public QDialog
{
    Q_OBJECT
public:
    PluginsDialog(QMap<QString, PropertiesPlugin*> plugins);

signals:

public slots:

private:
    QVBoxLayout *m_mainLayout;
    QStatusBar *mw_statusBar;
    QScrollArea *mw_scroll;
    QWidget *mw_container;
    QVBoxLayout *m_pluginsLayout;

private:
    void buildList(QMap<QString, PropertiesPlugin *> plugins);
};

#endif // PLUGINSDIALOG_H
