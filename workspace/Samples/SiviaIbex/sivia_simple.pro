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
 sivia.cpp \
 frame.cpp \
    vstablesolve.cpp \
    solve.cpp

HEADERS += mainwindow.h \
 frame.h \
 sivia.h \
    vstablesolve.h \
    solve.h

FORMS += mainwindow.ui

CONFIG += link_pkgconfig
PKGCONFIG += /usr/local/share/pkgconfig/ibex.pc
