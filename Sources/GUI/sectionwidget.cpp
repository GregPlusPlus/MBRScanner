#include "sectionwidget.h"

SectionWidget::SectionWidget(MBRTools::MBRSection section, QWidget *parent) : QWidget(parent)
{
    m_mainLayout = new QGridLayout;
    m_mainLayout->setSizeConstraint(QGridLayout::SetFixedSize);

    mw_color = new SectionColorWidget(this);

    mw_name = new QLabel(this);
    mw_length = new QLabel(this);
    mw_startByte = new QLabel(this);
    mw_percentage = new QLabel(this);

    mw_name->setToolTip(tr("Section name"));
    mw_length->setToolTip(tr("Section length"));
    mw_startByte->setToolTip(tr("Start byte"));
    mw_percentage->setToolTip(tr("Percentage of use of the MBR"));

    m_mainLayout->addWidget(mw_color, 0, 0, 2, 2);
    m_mainLayout->addWidget(mw_name, 0, 2, 1, 3);
    m_mainLayout->addWidget(mw_length, 1, 2, 1, 1);
    m_mainLayout->addWidget(mw_startByte, 1, 3, 1, 1);
    m_mainLayout->addWidget(mw_percentage, 1, 4, 1, 1);

    setLayout(m_mainLayout);

    setSection(section);
}

void SectionWidget::setSection(MBRTools::MBRSection section)
{
    mw_name->setText(section.name);
    mw_length->setText(QString::number(section.length));
    mw_startByte->setText(QString::number(section.startByte));
    mw_percentage->setText(tr("%1%").arg(QString::number((double)((double)section.length / (double)512) * 100, 'g', 2)));

    mw_color->setColor(section.color);
    mw_color->setPercentage((double)((double)section.length / (double)512));
}
