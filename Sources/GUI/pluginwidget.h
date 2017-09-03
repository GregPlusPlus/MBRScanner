#ifndef PLUGINWIDGET_H
#define PLUGINWIDGET_H

#include <QWidget>
#include <QLabel>

#include <QGridLayout>

#include "../PropertiesPlugin/propertiesplugin.h"

class PluginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PluginWidget(PropertiesPlugin *plugin, QWidget *parent = nullptr);

signals:

public slots:

private:
    QGridLayout *m_mainLayout;
    QLabel *mw_name;
    QLabel *mw_description;
    QLabel *mw_author;
    QLabel *mw_version;

};

#endif // PLUGINWIDGET_H
