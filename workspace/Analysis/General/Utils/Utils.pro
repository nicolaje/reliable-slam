#-------------------------------------------------
#
# Project created by QtCreator 2013-06-07T15:04:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Utils
TEMPLATE = lib


SOURCES += main.cpp\
        mainwindow.cpp \
    morsedataparser.cpp \
    morserosconnector.cpp \
    robot.cpp \
    sivia.cpp \
    positionloader.cpp

HEADERS  += mainwindow.h \
    morsedataparser.h \
    morserosconnector.h \
    robot.h \
    sivia.h \
    positionloader.h

FORMS    += mainwindow.ui
CONFIG += link_pkgconfig
PKGCONFIG += /usr/local/share/pkgconfig/ibex.pc
