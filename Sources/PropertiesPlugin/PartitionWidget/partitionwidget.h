#ifndef PARTITIONWIDGET_H
#define PARTITIONWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QFrame>
#include <QGroupBox>

#include <QVBoxLayout>
#include <QFormLayout>

#include <QPropertyAnimation>

#include <QDebug>

#include "partitionkeys.h"

namespace BinUtils
{
    enum Endianness{
        Little_Endianness,
        Big_Endianness
    };

    uint32_t changeEndianness(uint32_t value);
    uint32_t get32BitNumberFromArray(const QByteArray &array, int start, Endianness endianess);
}

class PartitionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PartitionWidget(int partitionId, QString name, QWidget *parent = 0);
    ~PartitionWidget();
    struct CHSAddress{
        uint16_t cylinder;
        uint8_t head;
        uint16_t sector;
    };

signals:

public slots:
    void toggle();
    void animFinished();
    void setData(QByteArray *data);
    void setName(QString name);
    void setPartitionId(int id);

private:
    QVBoxLayout *m_mainLayout;
    QFormLayout *m_dataLayout;
    QPushButton *mw_toggleButton;
    QWidget *mw_container;
    QVBoxLayout *mw_layoutContainer;
    QGroupBox *mw_firstSctrCHSGroup;
    QFormLayout *m_firstSctrCHSLayout;
    QGroupBox *mw_lastSctrCHSGroup;
    QFormLayout *m_lastSctrCHSLayout;

    QLineEdit *mw_physDrvStat;
    QLineEdit *mw_firstSctrH;
    QLineEdit *mw_firstSctrS;
    QLineEdit *mw_firstSctrC;
    QLineEdit *mw_partitionType;
    QLineEdit *mw_lastSctrH;
    QLineEdit *mw_lastSctrS;
    QLineEdit *mw_lastSctrC;
    QLineEdit *mw_LBASect;
    QLineEdit *mw_sectorCount;
    QCheckBox *mw_bootflag;

    int m_lastHeight;
    int m_pid;
    QString m_name;
    bool m_empty;

    QByteArray *m_data;
    QByteArray *m_partitionData;

    uint8_t m_physicalDriveStatus;
    CHSAddress m_chsAddressFirstSector;
    uint8_t m_partitionType;
    CHSAddress m_chsAddressLastSector;
    uint32_t m_LBAFirstSector;
    uint32_t m_sectorCount;

private:
    void createFields();
    void extractPartitionData();
    void parseMBR();
    void displayData();
    void displayOtherInfos();
    void checkForEmptyPartition();
    void displayEmptyPartition();

protected:
    void setStyleSheet(const QString &styleSheet);
};

#endif // PARTITIONWIDGET_H
