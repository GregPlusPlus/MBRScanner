#include "mbrinfowidget.h"

MBRInfoWidget::MBRInfoWidget(QWidget *parent) : QWidget(parent)
{
    m_mainLayout = new QVBoxLayout;

    mw_basicMBRInfoGroup = new QGroupBox(tr("Basic MBR infos"), this);

    m_basicMBRInfoLayout = new QVBoxLayout;
    mw_basicMBRInfoGroup->setLayout(m_basicMBRInfoLayout);

    mw_MBRType = new QLineEdit(this);
    mw_MBRType->setReadOnly(true);

    mw_driveBootable = new QCheckBox(tr("Is drive bootable"),this);
    mw_driveBootable->setEnabled(false);
    mw_driveBootable->setChecked(false);

    m_basicMBRInfoLayout->addWidget(mw_MBRType);
    m_basicMBRInfoLayout->addWidget(mw_driveBootable);

    mw_partitionsGroup = new QGroupBox(tr("Partitions"), this);

    m_partitionsLayout = new QVBoxLayout;
    mw_partitionsGroup->setLayout(m_partitionsLayout);

    mw_pw1 = new PartitionWidget(0, tr("Primary partition 1"), this);
    mw_pw2 = new PartitionWidget(1, tr("Primary partition 2"), this);
    mw_pw3 = new PartitionWidget(2, tr("Primary partition 3"), this);
    mw_pw4 = new PartitionWidget(3, tr("Primary partition 4"), this);
    m_partitionsLayout->addWidget(mw_pw1);
    m_partitionsLayout->addWidget(mw_pw2);
    m_partitionsLayout->addWidget(mw_pw3);
    m_partitionsLayout->addWidget(mw_pw4);

    m_mainLayout->addWidget(mw_basicMBRInfoGroup, 0, Qt::AlignTop);
    m_mainLayout->addWidget(mw_partitionsGroup, 0, Qt::AlignTop);

    setLayout(m_mainLayout);
}

void MBRInfoWidget::setData(QByteArray *data)
{
    setDriveBootable((uint8_t)data->at(0x1FE)==0x55 && (uint8_t)data->at(0x1FF)==0xAA);

    mw_pw1->setData(data);
    mw_pw2->setData(data);
    mw_pw3->setData(data);
    mw_pw4->setData(data);
}

void MBRInfoWidget::setMBRType(QString type)
{
    mw_MBRType->setText(type);
}

void MBRInfoWidget::setDriveBootable(bool bootable)
{
    mw_driveBootable->setChecked(bootable);
}
