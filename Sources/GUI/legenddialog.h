#ifndef LEGENDDIALOG_H
#define LEGENDDIALOG_H

#include <QWidget>
#include <QDialog>

#include <QGridLayout>

#include <QList>

#include <QDebug>

#include <cmath>

#include "PropertiesPlugin/propertiesplugin.h"
#include "GUI/sectionwidget.h"

class LegendDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LegendDialog(QWidget *parent = nullptr);
    ~LegendDialog();

signals:

public slots:
    void setPlugin(PropertiesPlugin *plugin);

private:
    QGridLayout *m_mainLayout;

    QList<SectionWidget*> m_sectionWidgets;

    PropertiesPlugin *m_plugin;

private:
    void updateSections();
};

#endif // LEGENDDIALOG_H
