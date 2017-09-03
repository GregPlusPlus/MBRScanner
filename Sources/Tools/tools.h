#ifndef TOOLS_H
#define TOOLS_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QFrame>
#include <QFile>
#include <QApplication>

namespace Tools
{
    QString getPasswordAsMask(QString password, QString mask);
    QFrame *createSeparator(QFrame::Shape shape = QFrame::HLine);
    void applyStyleSheet(QString path);
}

#endif // TOOLS_H
