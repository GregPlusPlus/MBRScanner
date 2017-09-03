#include "abouttools.h"

void AboutTools::showAboutDialog(QString appName, QWidget *parent)
{
    QMessageBox *about = new QMessageBox(parent);
    about->setWindowTitle(QObject::tr("About %1...").arg(appName));
    about->setIconPixmap(QPixmap(":/icons/icon"));
    about->setText(QObject::tr(ABOUT_TEXT).arg(appName).arg(QT_VERSION_STR));
    //about->setDetailedText(QObject::tr(""));
    about->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::LinksAccessibleByMouse | Qt::LinksAccessibleByKeyboard);
    about->setStandardButtons(QMessageBox::Close);
    about->setDefaultButton(QMessageBox::Close);

    QFile gpl(":/licenses/copying");
    QFile lgpl(":/licenses/copying.lesser");
    QFile CCBY30(":/licenses/legalcode");

    if(gpl.open(QIODevice::ReadOnly)){about->setDetailedText(about->detailedText() + gpl.readAll() + "\n\n");}
    if(lgpl.open(QIODevice::ReadOnly)){about->setDetailedText(about->detailedText() + lgpl.readAll() + "\n\n");}
    if(CCBY30.open(QIODevice::ReadOnly)){about->setDetailedText(about->detailedText() + CCBY30.readAll() + "\n\n");}

    about->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    about->exec();
}
