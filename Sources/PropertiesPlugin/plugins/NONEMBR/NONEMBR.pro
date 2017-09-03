QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG      += plugin
TARGET      = NONEMBR
VERSION     = 1.0.0

DESTDIR = ../../../release/PropertiesPlugins

TEMPLATE    = lib

SOURCES += \
        nonembr.cpp

HEADERS += \
        nonembr.h
