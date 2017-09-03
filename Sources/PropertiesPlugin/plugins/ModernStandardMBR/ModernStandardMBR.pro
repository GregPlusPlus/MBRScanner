QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG      += plugin
TARGET      = ModernStandardMBR
VERSION     = 1.0.0

Release:DESTDIR = ../../../release/PropertiesPlugins
Debug:DESTDIR = ../../../debug/PropertiesPlugins

TEMPLATE    = lib

SOURCES += \
        modernstandardmbr.cpp \
        mbrinfowidget.cpp

HEADERS += \
        modernstandardmbr.h \
        mbrinfowidget.h

include(../../PartitionWidget/PartitionWidget.pri)

