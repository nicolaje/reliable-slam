#-------------------------------------------------
#
# Project created by QtCreator 2013-06-07T15:04:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Utils
TEMPLATE = lib


SOURCES +=\
    morsedataparser.cpp \
    morserosconnector.cpp \
    robot.cpp \
    positionloader.cpp

HEADERS  += \
    morsedataparser.h \
    morserosconnector.h \
    robot.h \
    positionloader.h

FORMS    +=
CONFIG += link_pkgconfig
PKGCONFIG += /usr/local/share/pkgconfig/ibex.pc
