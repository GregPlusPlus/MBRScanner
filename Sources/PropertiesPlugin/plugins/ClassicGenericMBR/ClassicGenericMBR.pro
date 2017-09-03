QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG      += plugin
TARGET      = ClassicGenericMBR
VERSION     = 1.0.0

Release:DESTDIR = ../../../release/PropertiesPlugins
Debug:DESTDIR = ../../../debug/PropertiesPlugins

TEMPLATE    = lib

SOURCES += \
        classicgenericmbr.cpp \
        mbrinfowidget.cpp \
        ../../PartitionWidget/partitionkeys.cpp \
        ../../PartitionWidget/partitionwidget.cpp \

HEADERS += \
        classicgenericmbr.h \
        mbrinfowidget.h \
        ../../PartitionWidget/partitionkeys.h \
        ../../PartitionWidget/partitionwidget.h
