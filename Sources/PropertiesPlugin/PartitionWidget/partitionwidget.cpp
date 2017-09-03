#include "partitionwidget.h"

uint32_t BinUtils::changeEndianness(uint32_t value)
{
    uint32_t result = 0;
    result |= (value & 0x000000FF) << 24;
    result |= (value & 0x0000FF00) << 8;
    result |= (value & 0x00FF0000) >> 8;
    result |= (value & 0xFF000000) >> 24;
    return result;
}

uint32_t BinUtils::get32BitNumberFromArray(const QByteArray &array, int start, BinUtils::Endianness endianess)
{
    uint32_t result = 0;
    uint8_t *bytes = new uint8_t[4];

    for(int i = start ; i < start + 4 ; i++)
    {
        bytes[i - start] = (uint8_t)array.at(i);
    }
    memcpy(&result, bytes, sizeof(uint32_t));

    delete bytes;

    if(endianess == BinUtils::Big_Endianness)
    {
        result = BinUtils::changeEndianness(result);
    }

    return result;
}

PartitionWidget::PartitionWidget(int partitionId, QString name, QWidget *parent) : QWidget(parent), m_name(name)
{
    m_physicalDriveStatus   = 0;
    m_partitionType         = 0;
    m_LBAFirstSector        = 0;
    m_sectorCount           = 0;
    m_empty                 = false;

    m_pid = partitionId;

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setSpacing(0);
    m_mainLayout->setMargin(5);

    mw_toggleButton = new QPushButton(m_name, this);
    mw_toggleButton->setCheckable(true);
    mw_toggleButton->setChecked(true);
    mw_toggleButton->setStyleSheet("QPushButton{"
                                   "border: 1px solid #535D69;"
                                   "border-radius: 0px;"
                                   "border-top-left-radius: 4px;"
                                   "border-top-right-radius: 4px;"
                                   "padding: 2px;"
                                   "margin-top: 0px;"
                                   "background-color: #212930;"
                                   "}"
                                   "QPushButton:!checked{"
                                   "border-radius: 4px;"
                                   "background: #2F3740;"
                                   "}"
                                   "QPushButton:hover{"
                                   "background: #334452;"
                                   "}"
                                   "QPushButton:pressed{"
                                   "background: #101E2E;"
                                   "}");
    connect(mw_toggleButton, SIGNAL(clicked(bool)), this, SLOT(toggle()));

    mw_container = new QWidget(this);
    mw_container->setObjectName("container");
    mw_container->setStyleSheet("#container{"
                                "border: 1px solid #535D69;"
                                "border-bottom-left-radius: 4px;"
                                "border-bottom-right-radius: 4px;"
                                "padding: 2px;"
                                "margin-top: -1px;"
                                "}");
    mw_container->setMinimumHeight(400);
    mw_container->setMinimumWidth(300);

    mw_layoutContainer = new QVBoxLayout;
    m_dataLayout = new QFormLayout;

    mw_layoutContainer->addLayout(m_dataLayout);

    mw_container->setLayout(mw_layoutContainer);

    mw_firstSctrCHSGroup = new QGroupBox(tr("CHS address of first absolute sector"), this);
    m_firstSctrCHSLayout = new QFormLayout;
    mw_firstSctrCHSGroup->setLayout(m_firstSctrCHSLayout);

    mw_lastSctrCHSGroup = new QGroupBox(tr("CHS address of last absolute sector"), this);
    m_lastSctrCHSLayout = new QFormLayout;
    mw_lastSctrCHSGroup->setLayout(m_lastSctrCHSLayout);

    createFields();

    m_mainLayout->addWidget(mw_toggleButton);
    m_mainLayout->addWidget(mw_container);

    m_data = new QByteArray;
    m_partitionData = new QByteArray;

    setLayout(m_mainLayout);
}

PartitionWidget::~PartitionWidget()
{
    delete m_data;
    delete m_partitionData;
}

void PartitionWidget::toggle()
{
    int duration = 150;

    if(mw_toggleButton->isChecked())
    {
        mw_container->setVisible(true);

        QPropertyAnimation *animation = new QPropertyAnimation(mw_container, "size");
        animation->setDuration(duration);
        animation->setStartValue(QSize(mw_container->width(), 0));
        animation->setEndValue(QSize(mw_container->width(), m_lastHeight));

        connect(animation, SIGNAL(finished()), this, SLOT(animFinished()));

        animation->start();
    }
    else
    {
        mw_container->setMinimumHeight(0);
        m_lastHeight = mw_container->height();

        QPropertyAnimation *animation = new QPropertyAnimation(mw_container, "size");
        animation->setDuration(duration);
        animation->setStartValue(QSize(mw_container->width(), mw_container->height()));
        animation->setEndValue(QSize(mw_container->width(), 0));

        connect(animation, SIGNAL(finished()), this, SLOT(animFinished()));

        animation->start();
    }
}

void PartitionWidget::animFinished()
{
    if(mw_toggleButton->isChecked())
    {
        mw_container->setMinimumHeight(400);
    }
    else
    {
        mw_container->setVisible(false);
    }
}

void PartitionWidget::setData(QByteArray *data)
{
    m_partitionData->clear();
    m_data->setRawData(data->data(), data->length());

    extractPartitionData();
    parseMBR();
    displayData();
}

void PartitionWidget::setName(QString name)
{
    m_name = name;
    mw_toggleButton->setText(m_name);
}

void PartitionWidget::setPartitionId(int id)
{
    m_pid = id;

    parseMBR();
    displayData();
}

void PartitionWidget::createFields()
{
    mw_physDrvStat = new QLineEdit(tr("------"), this);
    mw_physDrvStat->setReadOnly(true);

    mw_firstSctrH = new QLineEdit(tr("------"), this);
    mw_firstSctrH->setReadOnly(true);

    mw_firstSctrS = new QLineEdit(tr("------"), this);
    mw_firstSctrS->setReadOnly(true);

    mw_firstSctrC = new QLineEdit(tr("------"), this);
    mw_firstSctrC->setReadOnly(true);

    mw_partitionType = new QLineEdit(tr("------"), this);
    mw_partitionType->setReadOnly(true);

    mw_lastSctrH = new QLineEdit(tr("------"), this);
    mw_lastSctrH->setReadOnly(true);

    mw_lastSctrS = new QLineEdit(tr("------"), this);
    mw_lastSctrS->setReadOnly(true);

    mw_lastSctrC = new QLineEdit(tr("------"), this);
    mw_lastSctrC->setReadOnly(true);

    mw_LBASect = new QLineEdit(tr("------"), this);
    mw_LBASect->setReadOnly(true);

    mw_sectorCount = new QLineEdit(tr("------"), this);
    mw_sectorCount->setReadOnly(true);

    mw_bootflag = new QCheckBox(tr("Is partition bootable"), this);
    mw_bootflag->setEnabled(false);

    m_dataLayout->addRow(new QLabel(tr("Status of physical drive")), mw_physDrvStat);
    m_dataLayout->addWidget(mw_firstSctrCHSGroup);
    m_dataLayout->addRow(new QLabel(tr("Partition type")), mw_partitionType);
    m_dataLayout->addWidget(mw_lastSctrCHSGroup);
    m_dataLayout->addRow(new QLabel(tr("LBA of first absolute sector")), mw_LBASect);
    m_dataLayout->addRow(new QLabel(tr("Number of sectors in partition")), mw_sectorCount);

    m_firstSctrCHSLayout->addRow(new QLabel(tr("Head of first absolute sector")), mw_firstSctrH);
    m_firstSctrCHSLayout->addRow(new QLabel(tr("Sector of first absolute sector")), mw_firstSctrS);
    m_firstSctrCHSLayout->addRow(new QLabel(tr("Cylinder of first absolute sector")), mw_firstSctrC);

    m_lastSctrCHSLayout->addRow(new QLabel(tr("Head of last absolute sector")), mw_lastSctrH);
    m_lastSctrCHSLayout->addRow(new QLabel(tr("Sector of last absolute sector")), mw_lastSctrS);
    m_lastSctrCHSLayout->addRow(new QLabel(tr("Cylinder of last absolute sector")), mw_lastSctrC);

    mw_layoutContainer->addWidget(mw_bootflag);
    mw_layoutContainer->addWidget(mw_firstSctrCHSGroup);
    mw_layoutContainer->addWidget(mw_lastSctrCHSGroup);
}

void PartitionWidget::extractPartitionData()
{
    int address = 0x1BE + (16*m_pid);

    for(int i = address ; i < address+16 ; i++)
    {
        m_partitionData->append(m_data->at(i));
    }
}

void PartitionWidget::parseMBR()
{
    m_physicalDriveStatus               = 0;
    m_partitionType                     = 0;
    m_LBAFirstSector                    = 0;
    m_sectorCount                       = 0;
    m_chsAddressFirstSector.head        = 0;
    m_chsAddressFirstSector.sector      = 0;
    m_chsAddressFirstSector.cylinder    = 0;
    m_chsAddressLastSector.head         = 0;
    m_chsAddressLastSector.sector       = 0;
    m_chsAddressLastSector.cylinder     = 0;

    m_physicalDriveStatus = (uint8_t)m_partitionData->at(0x00);

    m_chsAddressFirstSector.head     =  (uint8_t)m_partitionData->at(0x01);
    m_chsAddressFirstSector.sector   = (uint16_t)m_partitionData->at(0x02) & 0b00111111;
    m_chsAddressFirstSector.cylinder = (uint16_t)m_partitionData->at(0x03) | ((m_chsAddressFirstSector.sector & 0b11000000) << 2);

    m_partitionType = (uint8_t)m_partitionData->at(0x04);

    m_chsAddressLastSector.head     =  (uint8_t)m_partitionData->at(0x05);
    m_chsAddressLastSector.sector   = (uint16_t)m_partitionData->at(0x06) & 0b00111111;
    m_chsAddressLastSector.cylinder = (uint16_t)m_partitionData->at(0x07) | ((m_chsAddressLastSector.sector   & 0b11000000) << 2);

    m_LBAFirstSector = BinUtils::get32BitNumberFromArray(*m_partitionData, 0x08, BinUtils::Little_Endianness);

    m_sectorCount    = BinUtils::get32BitNumberFromArray(*m_partitionData, 0x0C, BinUtils::Little_Endianness);

    checkForEmptyPartition();
}

void PartitionWidget::checkForEmptyPartition()
{
    if(m_physicalDriveStatus                    == 0x0 &&
            m_chsAddressFirstSector.cylinder    == 0x0 &&
            m_chsAddressFirstSector.head        == 0x0 &&
            m_chsAddressFirstSector.sector      == 0x0 &&
            m_partitionType                     == 0x0 &&
            m_chsAddressLastSector.cylinder     == 0x0 &&
            m_chsAddressLastSector.head         == 0x0 &&
            m_chsAddressLastSector.sector       == 0x0 &&
            m_LBAFirstSector                    == 0x0 &&
            m_sectorCount                       == 0x0)
    {
        m_empty = true;
    }
    else
    {
        m_empty = false;
    }
}

void PartitionWidget::displayData()
{
    mw_physDrvStat->setText(tr("0x") + QString::number(m_physicalDriveStatus, 16));
    mw_firstSctrH->setText(QString::number(m_chsAddressFirstSector.head));
    mw_firstSctrS->setText(QString::number(m_chsAddressFirstSector.sector));
    mw_firstSctrC->setText(QString::number(m_chsAddressFirstSector.cylinder));
    mw_partitionType->setText(tr("0x") + QString::number(m_partitionType, 16));
    mw_lastSctrH->setText(QString::number(m_chsAddressLastSector.head));
    mw_lastSctrS->setText(QString::number(m_chsAddressLastSector.sector));
    mw_lastSctrC->setText(QString::number(m_chsAddressLastSector.cylinder));
    mw_LBASect->setText(QString::number(m_LBAFirstSector));
    mw_sectorCount->setText(QString::number(m_sectorCount));

    if(m_physicalDriveStatus == 0x80)
    {
        mw_bootflag->setChecked(true);
    }
    else
    {
        mw_bootflag->setChecked(false);
    }

    displayOtherInfos();
    displayEmptyPartition();
}

void PartitionWidget::displayOtherInfos()
{
    mw_partitionType->setToolTip(PartitionKeys::getPartitionIDFromType(m_partitionType));
    mw_partitionType->setText(tr("%1 (%2)").arg(mw_partitionType->text(), PartitionKeys::getPartitionIDFromType(m_partitionType)));

    mw_physDrvStat->setToolTip(PartitionKeys::getVolumeStatus(m_physicalDriveStatus));
    mw_physDrvStat->setText(tr("%1 (%2)").arg(mw_physDrvStat->text(), PartitionKeys::getVolumeStatus(m_physicalDriveStatus)));
}

void PartitionWidget::displayEmptyPartition()
{
    if(m_empty)
    {
        mw_toggleButton->setEnabled(false);
        mw_toggleButton->setText(tr("%1 (empty)").arg(m_name));

        if(mw_toggleButton->isChecked())
        {
            mw_toggleButton->setChecked(false);
            toggle();
        }
    }
    else
    {
        mw_toggleButton->setEnabled(true);
        mw_toggleButton->setText(m_name);

        if(!mw_toggleButton->isChecked())
        {
            mw_toggleButton->setChecked(true);
            toggle();
        }
    }
}

void PartitionWidget::setStyleSheet(const QString &styleSheet)
{
    Q_UNUSED (styleSheet)
}
