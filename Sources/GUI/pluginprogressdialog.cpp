#include "pluginprogressdialog.h"

PluginProgressDialog::PluginProgressDialog() : QDialog()
{
    setWindowTitle(tr("Loading plugins..."));
    setWindowIcon(QIcon(":/icons/hourglass"));

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setSizeConstraint(QGridLayout::SetFixedSize);

    mw_progress = new QProgressBar(this);
    mw_progress->setOrientation(Qt::Horizontal);
    mw_progress->setValue(0);

    mw_name = new QLabel(this);

    m_mainLayout->addWidget(mw_progress);
    m_mainLayout->addWidget(mw_name);

    setLayout(m_mainLayout);
}

void PluginProgressDialog::newPlugin(PropertiesPlugin *plugin)
{
    m_currentCount++;

    mw_progress->setValue(m_currentCount);
    mw_name->setText(tr("Plugin '%1' successfully loaded!").arg(plugin->getName()));
}

void PluginProgressDialog::setCount(int count)
{
    m_pluginCount = count;

    mw_progress->setMaximum(m_pluginCount);
}
