#ifndef MBRINFOWIDGET_H
#define MBRINFOWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QGroupBox>

#include <QByteArray>

#include <QVBoxLayout>

#include "partitionwidget.h"

class MBRInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MBRInfoWidget(QWidget *parent = nullptr);

signals:

public slots:
    void setData(QByteArray *data);
    void setMBRType(QString type);

private:
    QVBoxLayout *m_mainLayout;
    QVBoxLayout *m_basicMBRInfoLayout;
    QVBoxLayout *m_partitionsLayout;
    QGroupBox *mw_basicMBRInfoGroup;
    QGroupBox *mw_partitionsGroup;
    QLineEdit *mw_MBRType;
    QLineEdit *mw_diskTimestamp;
    QLineEdit *mw_diskSignature;
    QCheckBox *mw_driveBootable;
    QCheckBox *mw_copyProtected;

    PartitionWidget *mw_pw1;
    PartitionWidget *mw_pw2;
    PartitionWidget *mw_pw3;
    PartitionWidget *mw_pw4;

private:
    void setDriveBootable(bool bootable);
    void setDriveCopyProtected(bool copyProtected);

};

#endif // MBRINFOWIDGET_H
