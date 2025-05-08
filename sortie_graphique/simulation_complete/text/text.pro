CONFIG += c++11

TARGET = ex_05_text

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    invariants_mouvement.cc \
    text_viewer.cc

HEADERS += \
    text_viewer.h \
    ../general/Dessinable.h \
    ../general/Support.h
