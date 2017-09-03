#-------------------------------------------------
#
# Project created by QtCreator 2017-08-05T22:06:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MBRScanner
TEMPLATE = app

#CONFIG += console

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(QHexEdit/QHexEdit.pri)


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        Core/core.cpp \
        Core/binutils.cpp \
        Core/plugintools.cpp \
        Core/mbrtools.cpp \
        Core/hexdisplay.cpp \
        GUI/pluginsselectiondialog.cpp \
        GUI/driveselectiondialog.cpp \
        GUI/pluginprogressdialog.cpp \
        GUI/legenddialog.cpp \
        GUI/sectionwidget.cpp \
        GUI/pluginsdialog.cpp \
        GUI/pluginwidget.cpp \
        GUI/defaultpropertieswidget.cpp \
        GUI/sectioncolorwidget.cpp \
        AboutTools/abouttools.cpp \
        Tools/tools.cpp

HEADERS += \
        mainwindow.h \
        Core/core.h \
        Core/binutils.h \
        Core/plugintools.h \
        Core/mbrtools.h \
        Core/hexdisplay.h \
        PropertiesPlugin/interface.h \
        PropertiesPlugin/propertiesplugin.h \
        PropertiesPlugin/pluginstructures.h \
        GUI/pluginsselectiondialog.h \
        GUI/driveselectiondialog.h \
        GUI/pluginprogressdialog.h \
        GUI/legenddialog.h \
        GUI/sectionwidget.h \
        GUI/pluginsdialog.h \
        GUI/pluginwidget.h \
        GUI/defaultpropertieswidget.h \
        GUI/sectioncolorwidget.h \
        AboutTools/about.h \
        AboutTools/abouttools.h \
        Tools/tools.h


LIBS += -lKernel32 -lSetupapi

RESOURCES += \
    rc.qrc

RC_FILE = rc.rc
