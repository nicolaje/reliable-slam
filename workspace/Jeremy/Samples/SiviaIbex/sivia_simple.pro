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

win32 {
 INCLUDEPATH += ../ibex-2.0/include/ibex ../soplex-1.7.0/src
 LIBS += -L../ibex-2.0/bin -L../soplex-1.7.0/lib -libex_mingw_x86 -lsoplex_mingw_x86
} 
else {
 INCLUDEPATH += ../ibex-2.0/include/ibex ../soplex-1.7.0/src
 LIBS += -L../ibex-2.0/bin -L../soplex-1.7.0/lib -libex_linux_x86 -lsoplex_linux_x86
}
