#ifndef PLUGINPROGRESSDIALOG_H
#define PLUGINPROGRESSDIALOG_H

#include <QDialog>
#include <QProgressBar>
#include <QLabel>

#include <QVBoxLayout>

#include <QIcon>
#include <QString>

#include "PropertiesPlugin/propertiesplugin.h"

class PluginProgressDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PluginProgressDialog();
    void newPlugin(PropertiesPlugin *plugin);
    void setCount(int count);

signals:

private:
    QVBoxLayout *m_mainLayout;
    QProgressBar *mw_progress;
    QLabel *mw_name;

    int m_pluginCount;
    int m_currentCount;
};

#endif // PLUGINPROGRESSDIALOG_H
