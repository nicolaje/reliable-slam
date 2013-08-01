#-------------------------------------------------
#
# Project created by QtCreator 2013-07-06T19:12:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IBEXPlayground
TEMPLATE = app


SOURCES += main.cpp

HEADERS  +=

FORMS    +=
CONFIG += link_pkgconfig
PKGCONFIG +=/usr/local/share/pkgconfig/ibex.pc
PKGCONFIG +=/usr/lib/pkgconfig/eigen3.pc
