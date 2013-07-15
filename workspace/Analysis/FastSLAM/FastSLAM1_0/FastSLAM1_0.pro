#-------------------------------------------------
#
# Project created by QtCreator 2013-06-07T14:56:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FastSLAM1_0
TEMPLATE = app


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
LIBS += -L"../../General/Utils-build-desktop-Qt_4_8_2_in_PATH__System__Release/" -lUtils
