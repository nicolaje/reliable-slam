#-------------------------------------------------
#
# Project created by QtCreator 2013-07-30T23:17:34
#
#-------------------------------------------------
QT       += core gui

TEMPLATE = app
TARGET = BESEFastSLAM
CONFIG += c++11

SOURCES += main.cpp \
    besefastslam.cpp \
    ../../IntervalAnalysis/BoundedErrorStateEstimatorSLAM/bese.cpp \
    ../../FastSLAM/FastSLAM1_0/fastslam.cpp \
    ../../FastSLAM/FastSLAM1_0/particle.cpp \
    ../../FastSLAM/FastSLAM1_0/kalmanfilter.cpp \
    ../../FastSLAM/FastSLAM1_0/resampling.cpp

HEADERS += \
    besefastslam.h \
    ../../IntervalAnalysis/BoundedErrorStateEstimatorSLAM/bese.h \
    ../../FastSLAM/FastSLAM1_0/fastslam.h \
    ../../FastSLAM/FastSLAM1_0/particle.h \
    ../../FastSLAM/FastSLAM1_0/kalmanfilter.h \
    ../../FastSLAM/FastSLAM1_0/resampling.h

CONFIG += link_pkgconfig
PKGCONFIG +=/usr/local/share/pkgconfig/ibex.pc
PKGCONFIG +=/usr/lib/pkgconfig/eigen3.pc
LIBS += -L"../../General/build-Utils-Desktop_Qt_5_1_0_GCC_64bit-Debug/" -lUtils
