#-------------------------------------------------
#
# Project created by QtCreator 2013-06-13T14:57:28
#
#-------------------------------------------------

QT       += core gui

TARGET = Localizacao
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    iboolean.cpp \
    dados.cpp \
    particula.cpp \
    landmark.cpp \
    imagem.cpp \
    paletacores.cpp \
    filtroParticulas.cpp \
    sivia.cpp \
    hibrido.cpp

HEADERS  += mainwindow.h \
    iboolean.h \
    dados.h \
    configuracaoes.h \
    particula.h \
    sivia.h \
    landmark.h \
    imagem.h \
    paletacores.h \
    filtroParticulas.h \
    sivia.h \
    hibrido.h

FORMS    += mainwindow.ui

CONFIG += link_pkgconfig
PKGCONFIG += /usr/local/share/pkgconfig/ibex.pc
