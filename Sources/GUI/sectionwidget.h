#ifndef SECTIONWIDGET_H
#define SECTIONWIDGET_H

#include <QWidget>
#include <QLabel>

#include <QGridLayout>

#include <QString>
#include <QColor>
#include <QPalette>

#include "../Core/mbrtools.h"

#include "sectioncolorwidget.h"

class SectionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SectionWidget(MBRTools::MBRSection section, QWidget *parent = nullptr);

signals:

public slots:
    void setSection(MBRTools::MBRSection section);

private:
    QGridLayout *m_mainLayout;
    SectionColorWidget *mw_color;
    QLabel *mw_name;
    QLabel *mw_length;
    QLabel *mw_startByte;
    QLabel *mw_percentage;
};

#endif // SECTIONWIDGET_H
