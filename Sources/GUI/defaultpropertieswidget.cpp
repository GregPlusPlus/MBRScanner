#include "defaultpropertieswidget.h"

DefaultPropertiesWidget::DefaultPropertiesWidget(QWidget *parent) : QWidget(parent)
{
    m_mainLayout = new QVBoxLayout;

    QFont f("Arial", 30, QFont::Bold);
    mw_title = new QLabel(tr("No data"));
    mw_title->setAlignment(Qt::AlignCenter);
    mw_title->setFont(f);

    f = QFont("Arial", 10, QFont::Bold);

    mw_message = new QLabel(tr("To open the MBR go to : <br><i>File 🢒 Open... 🢒 Load MBR from drive</i><br> Then, choose a drive and a plugin."));
    mw_message->setAlignment(Qt::AlignCenter);
    mw_message->setFont(f);

    m_mainLayout->addWidget(mw_title, Qt::AlignTop);
    m_mainLayout->addWidget(mw_message, Qt::AlignTop);

    setLayout(m_mainLayout);
}
