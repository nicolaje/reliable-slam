#-------------------------------------------------
#
# Project created by QtCreator 2013-06-07T14:52:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BoundedErrorStateEstimatorSLAM
TEMPLATE = app

SOURCES += main.cpp\
    bese.cpp \

HEADERS  += \
    bese.h \

FORMS    +=
CONFIG += link_pkgconfig
PKGCONFIG +=/usr/local/share/pkgconfig/ibex.pc
PKGCONFIG +=/usr/lib/pkgconfig/eigen3.pc
LIBS += -L"../../General/build-Utils-Desktop_Qt_5_1_0_GCC_64bit-Debug/" -lUtils
