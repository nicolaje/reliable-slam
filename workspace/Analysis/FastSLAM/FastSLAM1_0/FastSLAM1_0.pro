#-------------------------------------------------
#
# Project created by QtCreator 2013-06-07T14:56:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FastSLAM1_0
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    particle.cpp \
    resampling.cpp \
    kalmanfilter.cpp \
    fastslam.cpp

HEADERS  += mainwindow.h \
    particle.h \
    resampling.h \
    kalmanfilter.h \
    fastslam.h

FORMS    += mainwindow.ui
CONFIG += link_pkgconfig
PKGCONFIG +=/usr/local/share/pkgconfig/ibex.pc
PKGCONFIG +=/usr/lib/pkgconfig/eigen3.pc
LIBS += -L"../../General/build-Utils-Desktop_Qt_5_1_0_GCC_64bit-Debug/" -lUtils
