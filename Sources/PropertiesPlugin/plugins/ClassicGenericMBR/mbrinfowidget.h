#ifndef MBRINFOWIDGET_H
#define MBRINFOWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QGroupBox>

#include <QByteArray>

#include <QVBoxLayout>

#include "../../PartitionWidget/partitionwidget.h"

class MBRInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MBRInfoWidget(QWidget *parent = nullptr);

signals:

public slots:
    void setData(QByteArray *data);
    void setMBRType(QString type);
    void setDriveBootable(bool bootable);

private:
    QVBoxLayout *m_mainLayout;
    QVBoxLayout *m_basicMBRInfoLayout;
    QVBoxLayout *m_partitionsLayout;
    QGroupBox *mw_basicMBRInfoGroup;
    QGroupBox *mw_partitionsGroup;
    QLineEdit *mw_MBRType;
    QCheckBox *mw_driveBootable;

    PartitionWidget *mw_pw1;
    PartitionWidget *mw_pw2;
    PartitionWidget *mw_pw3;
    PartitionWidget *mw_pw4;

};

#endif // MBRINFOWIDGET_H
