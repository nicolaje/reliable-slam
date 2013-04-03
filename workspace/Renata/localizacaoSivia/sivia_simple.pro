#-------------------------------------------------
#
# Project created by QtCreator 2011-07-01T09:24:59
#
#-------------------------------------------------

QT       += core gui

TARGET = sivia_simple
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    interval.cpp \
    iboolean.cpp \
    box.cpp \
    repere.cpp \
    particula.cpp \
    landmark.cpp \
    arquivos.cpp

HEADERS  += mainwindow.h \
    interval.h \
    iboolean.h \
    box.h \
    repere.h \
    particula.h \
    landmark.h \
    incluir.h \
    arquivos.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++0x

