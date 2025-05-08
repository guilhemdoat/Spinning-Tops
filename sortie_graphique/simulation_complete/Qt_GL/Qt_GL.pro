QT += core gui opengl widgets
CONFIG += c++11

win32:LIBS += -lopengl32


TARGET = ex_05_gl

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    main_qt_gl.cc \
    glwidget.cc \
    vue_opengl.cc

HEADERS += \
    ../general/ConeSimple.h \
    glwidget.h \
    vertex_shader.h \
    vue_opengl.h \
    ../general/Dessinable.h \
    ../general/Support.h

RESOURCES += \
    resource.qrc
