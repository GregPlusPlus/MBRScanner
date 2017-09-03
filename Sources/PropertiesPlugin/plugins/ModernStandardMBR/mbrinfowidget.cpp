#include "mbrinfowidget.h"

MBRInfoWidget::MBRInfoWidget(QWidget *parent) : QWidget(parent)
{
    m_mainLayout = new QVBoxLayout;

    mw_basicMBRInfoGroup = new QGroupBox(tr("Basic MBR infos"), this);

    m_basicMBRInfoLayout = new QVBoxLayout;
    mw_basicMBRInfoGroup->setLayout(m_basicMBRInfoLayout);

    mw_MBRType = new QLineEdit(this);
    mw_MBRType->setReadOnly(true);

    mw_diskTimestamp = new QLineEdit(this);
    mw_diskTimestamp->setReadOnly(true);

    mw_diskSignature = new QLineEdit(this);
    mw_diskSignature->setReadOnly(true);

    mw_driveBootable = new QCheckBox(tr("Is drive bootable"),this);
    mw_driveBootable->setEnabled(false);
    mw_driveBootable->setChecked(false);

    mw_copyProtected = new QCheckBox(tr("Is drive copy-protected"),this);
    mw_copyProtected->setEnabled(false);
    mw_copyProtected->setChecked(false);

    m_basicMBRInfoLayout->addWidget(mw_MBRType);
    m_basicMBRInfoLayout->addWidget(new QLabel(tr("Disk timestamp")));
    m_basicMBRInfoLayout->addWidget(mw_diskTimestamp);
    m_basicMBRInfoLayout->addWidget(new QLabel(tr("Disk signature")));
    m_basicMBRInfoLayout->addWidget(mw_diskSignature);
    m_basicMBRInfoLayout->addWidget(mw_driveBootable);
    m_basicMBRInfoLayout->addWidget(mw_copyProtected);

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
    m_mainLayout->addWidget(mw_partitionsGroup,   0, Qt::AlignTop);

    setLayout(m_mainLayout);
}

void MBRInfoWidget::setData(QByteArray *data)
{
    setDriveBootable     ((uint8_t)data->at(0x1FE) == 0x55 && (uint8_t)data->at(0x1FF) == 0xAA);
    setDriveCopyProtected((uint8_t)data->at(0x1BC) == 0x5A && (uint8_t)data->at(0x1BD) == 0x5A);

    QByteArray ts;

    for(int i = 0x0DA ; i < 0x0DA+6 ; i++)
    {
        ts.append(data->at(i));
    }

    QByteArray ds;

    for(int i = 0x1B8 ; i < 0x1B8+4 ; i++)
    {
        ds.append(data->at(i));
    }

    mw_diskTimestamp->setText(tr("0x%1").arg(QString(ts.toHex()).toUpper()));
    mw_diskSignature->setText(tr("0x%1").arg(QString(ds.toHex()).toUpper()));

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

void MBRInfoWidget::setDriveCopyProtected(bool copyProtected)
{
    mw_copyProtected->setChecked(copyProtected);
}
