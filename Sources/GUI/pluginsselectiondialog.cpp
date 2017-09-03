#include "pluginsselectiondialog.h"

PluginsSelectionDialog::PluginsSelectionDialog(QMap<QString, PropertiesPlugin*> &plugins, QWidget *parent) : QDialog(parent), m_plugins(plugins)
{
    setWindowTitle(tr("Select a plugin"));
    setWindowIcon(QIcon(":/icons/puzzle"));

    m_mainLayout = new QGridLayout;
    m_mainLayout->setSizeConstraint(QGridLayout::SetFixedSize);

    mw_text = new QLabel(tr("Select a plugin: "), this);

    mw_comboBox = new QComboBox(this);
    mw_comboBox->addItems(m_plugins.keys());
    connect(mw_comboBox, SIGNAL(activated(int)), this, SLOT(updateSelectedPlugin()));
    updateSelectedPlugin();

    mw_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, Qt::Horizontal, this);
    connect(mw_buttonBox, SIGNAL(accepted()), this, SLOT(close()));

    m_mainLayout->addWidget(mw_text, 0, 0, 1, 1);
    m_mainLayout->addWidget(mw_comboBox, 0, 1, 1, 1);
    m_mainLayout->addWidget(mw_buttonBox, 1, 0, 1, 2, Qt::AlignBottom);

    setLayout(m_mainLayout);
}

PropertiesPlugin *PluginsSelectionDialog::selectPlugin(QMap<QString, PropertiesPlugin *> &plugins)
{
    PluginsSelectionDialog dialog(plugins);
    dialog.exec();

    return dialog.selectedPlugin();
}

PropertiesPlugin *PluginsSelectionDialog::selectedPlugin() const
{
    return m_selectedPlugin;
}

void PluginsSelectionDialog::updateSelectedPlugin()
{
    m_selectedPlugin = m_plugins.value(mw_comboBox->currentText());
}
