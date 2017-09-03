#include "pluginsdialog.h"

PluginsDialog::PluginsDialog(QMap<QString, PropertiesPlugin *> plugins): QDialog()
{
    setWindowTitle(tr("Available plugins"));
    setWindowIcon(QIcon(":/icons/puzzle"));
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint);

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setMargin(0);

    mw_statusBar = new QStatusBar(this);
    mw_statusBar->setSizeGripEnabled(false);
    //mw_statusBar->setStyleSheet("background: #29343d;");

    mw_scroll = new QScrollArea(this);
    mw_scroll->setWidgetResizable(true);

    mw_container = new QWidget(this);

    m_pluginsLayout = new QVBoxLayout;
    m_pluginsLayout->setMargin(20);
    mw_container->setLayout(m_pluginsLayout);

    mw_scroll->setWidget(mw_container);

    m_mainLayout->addWidget(mw_scroll);
    m_mainLayout->addWidget(mw_statusBar);

    setLayout(m_mainLayout);

    buildList(plugins);

    setMinimumWidth(300);
}

void PluginsDialog::buildList(QMap<QString, PropertiesPlugin *> plugins)
{
    for(int i = 0 ; i < plugins.keys().length() ; i++)
    {
        PluginWidget *w = new PluginWidget(plugins.value(plugins.keys().at(i)), this);

        m_pluginsLayout->addWidget(w, Qt::AlignTop);
        m_pluginsLayout->addWidget(Tools::createSeparator(), Qt::AlignTop);
    }

    mw_statusBar->showMessage(tr("%1 plugin(s) loaded in total.").arg(plugins.count()));
}
