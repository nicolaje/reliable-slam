#-------------------------------------------------
#
# Project created by QtCreator 2013-07-30T23:17:34
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = BESEFastSLAM
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    besefastslam.cpp

HEADERS += \
    besefastslam.h

CONFIG += link_pkgconfig
PKGCONFIG +=/usr/local/share/pkgconfig/ibex.pc
PKGCONFIG +=/usr/lib/pkgconfig/eigen3.pc
