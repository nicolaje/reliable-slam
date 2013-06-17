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
    kalmanfilter.cpp

HEADERS  += mainwindow.h \
    particle.h \
    resampling.h \
    kalmanfilter.h

FORMS    += mainwindow.ui
