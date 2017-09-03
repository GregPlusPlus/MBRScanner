#ifndef ABOUTTOOLS_H
#define ABOUTTOOLS_H

#include <QObject>
#include <QWidget>
#include <QMessageBox>
#include <QIcon>

#include <QFile>

#include "about.h"

namespace AboutTools
{
    void showAboutDialog(QString appName, QWidget *parent);
}

#endif // ABOUTTOOLS_H
