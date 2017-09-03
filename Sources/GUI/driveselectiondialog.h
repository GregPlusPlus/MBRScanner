#ifndef DRIVESELECTIONDIALOG_H
#define DRIVESELECTIONDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>

#include <QString>
#include <QStringList>

#include <QGridLayout>

#include <QDebug>

#include "Core/mbrtools.h"

class DriveSelectionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DriveSelectionDialog(QWidget *parent = nullptr);
    static QString selectDrive();

    QString selectedDrive();

signals:

public slots:
    void updateSelectedDrive();

private:
    QGridLayout *m_mainLayout;
    QDialogButtonBox *mw_buttonBox;
    QLabel *mw_text;
    QComboBox *mw_comboBox;

    QString m_path;

private:
    void populateComboBox();

};

#endif // DRIVESELECTIONDIALOG_H
