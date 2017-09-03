#include "pluginwidget.h"

PluginWidget::PluginWidget(PropertiesPlugin *plugin, QWidget *parent) : QWidget(parent)
{   
    m_mainLayout = new QGridLayout;
    m_mainLayout->setSizeConstraint(QGridLayout::SetFixedSize);

    mw_name = new QLabel(tr("<strong>%1</strong>").arg(plugin->getName()), this);
    mw_description = new QLabel(tr("<i>%1</i>").arg(plugin->getPluginInfo().description), this);
    mw_author = new QLabel(tr("%1").arg(plugin->getPluginInfo().author), this);
    mw_version = new QLabel(tr("V%1").arg(plugin->getPluginInfo().version), this);

    m_mainLayout->addWidget(mw_name, 0, 0, 1, 2);
    m_mainLayout->addWidget(mw_description, 1, 0, 1, 2);
    m_mainLayout->addWidget(mw_author, 2, 0, 1, 1);
    m_mainLayout->addWidget(mw_version, 2, 1, 1, 1);

    setLayout(m_mainLayout);
}
