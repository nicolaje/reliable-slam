#-------------------------------------------------
#
# Project created by QtCreator 2013-06-13T14:57:28
#
#-------------------------------------------------

QT       += core

TARGET = Localizacao
TEMPLATE = app


SOURCES += main.cpp\
    iboolean.cpp \
    dados.cpp \
    particula.cpp \
    landmark.cpp \
    filtroParticulas.cpp \
    hibrido.cpp \
    robo.cpp

HEADERS  += \
    iboolean.h \
    dados.h \
    configuracaoes.h \
    particula.h \
    landmark.h \
    filtroParticulas.h \
    hibrido.h \
    robo.h

FORMS    +=

CONFIG += link_pkgconfig
PKGCONFIG += /usr/local/share/pkgconfig/ibex.pc
