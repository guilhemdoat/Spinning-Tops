TEMPLATE = lib

CONFIG = staticlib c++11

SOURCES += \
    ConeSimple.cc \
    Dessinable.cc \
    IntEulCromer.cc \
    Integrateur.cc \
    Matrice33.cc \
    Systeme.cc \
    Toupie.cc \
    Vecteur.cc \
    integrateurrungekutta.cpp \
    intnewmark.cpp \
    constante.cc \
    toupiegenerale.cpp

HEADERS += \
    ConeSimple.h \
    Dessinable.h \
    Toupie.h \
    Systeme.h \
    Support.h \
    Vecteur.h \
    Matrice33.h \
    Integrateur.h \
    IntEulCromer.h \
    integrateurrungekutta.h \
    intnewmark.h \
    constante.h \
    toupiegenerale.h

