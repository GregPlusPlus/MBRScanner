#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("MBR Scanner"));
    setWindowIcon(QIcon(":/icons/main-icon"));
    Tools::applyStyleSheet(":/css/app.qss");

    initApp();
}

MainWindow::~MainWindow()
{
    delete mw_legendDialog;
    delete mw_pluginsDialog;
    delete m_data;
}

void MainWindow::initApp()
{
    initComponents();
    initUI();
    initMenus();
}

void MainWindow::initComponents()
{
    m_currentPlugin = nullptr;
    m_data = new QByteArray;

    loadPlugins();

    if(!m_plugins.keys().length())
    {
        QMessageBox::critical(this, tr("No plugin !!"), tr("No plugin were loaded. <br> Some informations may not be displayed."));
    }
}

void MainWindow::initUI()
{
    statusBar()->show();

    mw_legendDialog = new LegendDialog();
    mw_pluginsDialog = new PluginsDialog(m_plugins);

    mw_splitter = new QSplitter(this);

    mw_hexEdit = new QHexEdit(this);
    mw_hexEdit->setMinimumSize(700, 600);
    mw_hexEdit->setReadOnly(true);

    mw_scroll = new QScrollArea(this);
    mw_scroll->setWidgetResizable(true);
    mw_scroll->setMinimumWidth(400);

    mw_propertiesWidget = new DefaultPropertiesWidget(mw_scroll);
    mw_scroll->setWidget(mw_propertiesWidget);

    mw_splitter->addWidget(mw_hexEdit);
    mw_splitter->addWidget(mw_scroll);

    setCentralWidget(mw_splitter);
}

void MainWindow::initMenus()
{
    mw_fileMenu = menuBar()->addMenu(tr("&File"));
    mw_viewMenu = menuBar()->addMenu(tr("&View"));
    mw_helpMenu = menuBar()->addMenu(tr("&?"));

    mw_loadMenu = mw_fileMenu->addMenu(QIcon(":/icons/folder-horizontal-open"), tr("&Load..."));
    m_saveMBR = mw_fileMenu->addAction(QIcon(":/icons/disk"), tr("&Save MBR"), this, SLOT(saveMBR()), QKeySequence::Save);
    mw_fileMenu->addSeparator();
    mw_quitAction = mw_fileMenu->addAction(QIcon(":/icons/door-open-out"), tr("&Quit"), qApp, SLOT(quit()), QKeySequence(Qt::ALT + Qt::Key_Q));

    m_loadMBR = mw_loadMenu->addAction(QIcon(":/icons/hdd"), tr("Load MBR from drive"), this, SLOT(loadMBR()), QKeySequence::Open);
    m_loadMBRFromFile = mw_loadMenu->addAction(QIcon(":/icons/document-binary"), tr("Load MBR from file"), this, SLOT(loadMBRFromFile()), QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_O));

    m_showLegend = mw_viewMenu->addAction(QIcon(":/icons/block"), tr("&Legend"), this, SLOT(showLegend()), QKeySequence(Qt::CTRL + Qt::Key_F10));
    mw_viewMenu->addSeparator();
    m_showPlugins = mw_viewMenu->addAction(QIcon(":/icons/puzzle"), tr("&Plugins"), this, SLOT(showLoadedPlugins()), QKeySequence(Qt::CTRL + Qt::Key_F11));

    m_aboutAction = mw_helpMenu->addAction(QIcon(":/icons/information-button"), tr("&About MBR Scanner..."), this, SLOT(showAboutDialog()));
}

void MainWindow::loadMBR()
{
    if(Core::loadMBR(this,
                     &m_currentPlugin,
                     m_plugins,
                     mw_legendDialog,
                     m_data,
                     mw_hexEdit,
                     m_hexDocument,
                     &mw_propertiesWidget,
                     mw_scroll))statusBar()->showMessage(tr("MBR Successfully loaded! (%1)").arg((m_currentPlugin)?m_currentPlugin->getName():tr("No plugin")), 5000);
}

void MainWindow::loadMBRFromFile()
{
    if(Core::loadMBRFromFile(this,
                             &m_currentPlugin,
                             m_plugins,
                             mw_legendDialog,
                             m_data,
                             mw_hexEdit,
                             m_hexDocument,
                             &mw_propertiesWidget,
                             mw_scroll))statusBar()->showMessage(tr("File successfully loaded! (%1)").arg((m_currentPlugin)?m_currentPlugin->getName():tr("No plugin")), 5000);
}

void MainWindow::showLegend()
{
    if(m_currentPlugin)
    {
        mw_legendDialog->show();
    }
}

void MainWindow::showLoadedPlugins()
{
    mw_pluginsDialog->show();
}

void MainWindow::showAboutDialog()
{
    AboutTools::showAboutDialog("MBR Scanner", this);
}

void MainWindow::saveMBR()
{
    if(Core::saveMBR(this, m_data))statusBar()->showMessage(tr("File saved!"), 5000);
}

void MainWindow::loadPlugins()
{
    PluginTools::loadPlugins(m_plugins, true);
}
