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
        mainwindow.cpp\
    bese.cpp \

HEADERS  += mainwindow.h \
    bese.h \

FORMS    += mainwindow.ui
CONFIG += link_pkgconfig
PKGCONFIG +=/usr/local/share/pkgconfig/ibex.pc
PKGCONFIG +=/usr/lib/pkgconfig/eigen3.pc
LIBS += -L"../../General/Utils-build-desktop-Qt_4_8_2_in_PATH__System__Release/" -lUtils
