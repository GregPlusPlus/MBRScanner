#include "driveselectiondialog.h"

DriveSelectionDialog::DriveSelectionDialog(QWidget *parent): QDialog(parent)
{
    setWindowTitle(tr("Select a drive"));
    setWindowIcon(QIcon(":/icons/drive"));

    m_mainLayout = new QGridLayout;
    m_mainLayout->setSizeConstraint(QGridLayout::SetFixedSize);

    mw_text = new QLabel(tr("Select a drive: "), this);

    mw_comboBox = new QComboBox(this);
    populateComboBox();
    connect(mw_comboBox, SIGNAL(activated(int)), this, SLOT(updateSelectedDrive()));
    updateSelectedDrive();

    mw_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, Qt::Horizontal, this);
    connect(mw_buttonBox, SIGNAL(accepted()), this, SLOT(close()));

    m_mainLayout->addWidget(mw_text, 0, 0, 1, 1);
    m_mainLayout->addWidget(mw_comboBox, 0, 1, 1, 1);
    m_mainLayout->addWidget(mw_buttonBox, 1, 0, 1, 2, Qt::AlignBottom);

    setLayout(m_mainLayout);
}

QString DriveSelectionDialog::selectDrive()
{
    DriveSelectionDialog dialog;
    dialog.exec();

    return dialog.selectedDrive();
}

QString DriveSelectionDialog::selectedDrive()
{
    return m_path;
}

void DriveSelectionDialog::updateSelectedDrive()
{
    m_path = mw_comboBox->currentText();
}

void DriveSelectionDialog::populateComboBox()
{
    QStringList drives = MBRTools::getMountedDrives();

    mw_comboBox->addItems(MBRTools::getPhysicalDisks());

    for(int i = 0 ; i < drives.length() ; i++)
    {
        mw_comboBox->addItem(tr("\\\\.\\%1").arg(drives.at(i).left(2)));
    }
}
