#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QScrollArea>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStatusBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QSplitter>
#include <QGridLayout>

#include <QMessageBox>
#include <QFileDialog>

#include <QKeySequence>
#include <QPalette>

#include <QDataStream>
#include <QByteArray>
#include <QList>
#include <QMap>
#include <QFile>

#include <QPluginLoader>
#include <QtConcurrent/QtConcurrent>

#include <QDebug>

#include <qhexedit.h>

#include "Core/core.h"
#include "Core/binutils.h"
#include "Core/plugintools.h"
#include "Core/mbrtools.h"
#include "Tools/tools.h"
#include "Core/hexdisplay.h"
#include "GUI/pluginsselectiondialog.h"
#include "GUI/driveselectiondialog.h"
#include "GUI/legenddialog.h"
#include "GUI/pluginsdialog.h"
#include "GUI/defaultpropertieswidget.h"
#include "AboutTools/about.h"
#include "AboutTools/abouttools.h"

#include "PropertiesPlugin/propertiesplugin.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void loadMBR();
    void loadMBRFromFile();
    void showLegend();
    void showLoadedPlugins();
    void showAboutDialog();
    void saveMBR();

private:
    QSplitter *mw_splitter;
    QHexEdit *mw_hexEdit;
    QScrollArea *mw_scroll;
    QWidget *mw_propertiesWidget;

    QMenu *mw_fileMenu;
    QMenu *mw_loadMenu;
    QMenu *mw_viewMenu;
    QMenu *mw_helpMenu;
    QAction *m_loadMBR;
    QAction *m_loadMBRFromFile;
    QAction *m_saveMBR;
    QAction *mw_quitAction;
    QAction *m_showLegend;
    QAction *m_showPlugins;
    QAction *m_aboutAction;

    QByteArray *m_data;
    QHexDocument *m_hexDocument;

    LegendDialog *mw_legendDialog;
    PluginsDialog *mw_pluginsDialog;

    PropertiesPlugin *m_currentPlugin;
    QMap<QString, PropertiesPlugin*> m_plugins;

    void loadPlugins();
    void initComponents();
    void initApp();
    void initUI();
    void initMenus();

private:

protected:

};

#endif // MAINWINDOW_H
