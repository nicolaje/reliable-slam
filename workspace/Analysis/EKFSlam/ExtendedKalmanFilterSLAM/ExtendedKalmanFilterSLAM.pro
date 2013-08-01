#-------------------------------------------------
#
# Project created by QtCreator 2013-06-07T15:02:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ExtendedKalmanFilterSLAM
TEMPLATE = app

SOURCES += main.cpp\
    ekfslam.cpp

HEADERS  += \
    ekfslam.h

PKGCONFIG +=/usr/lib/pkgconfig/eigen3.pc
