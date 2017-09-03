#ifndef PLUGINSSELECTIONDIALOG_H
#define PLUGINSSELECTIONDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>

#include <QGridLayout>

#include "PropertiesPlugin/propertiesplugin.h"

class PluginsSelectionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PluginsSelectionDialog(QMap<QString, PropertiesPlugin*> &plugins, QWidget *parent = nullptr);
    static PropertiesPlugin* selectPlugin(QMap<QString, PropertiesPlugin*> &plugins);

    PropertiesPlugin *selectedPlugin() const;

signals:

public slots:
    void updateSelectedPlugin();

private:
    QGridLayout *m_mainLayout;
    QLabel *mw_text;
    QComboBox *mw_comboBox;
    QDialogButtonBox *mw_buttonBox;

    QMap<QString, PropertiesPlugin*> m_plugins;
    PropertiesPlugin *m_selectedPlugin;
};

#endif // PLUGINSSELECTIONDIALOG_H
