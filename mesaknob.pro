#-------------------------------------------------
#
# Project created by QtCreator 2017-08-18T15:39:02
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mesaknob
TEMPLATE = app


SOURCES += main.cpp\
    powermate.cpp \
    knobmanager.cpp \
    knobbox.cpp \
    mainwindow.cpp \
    pv_list.cpp \
    value_label.cpp \
    config_list.cpp

HEADERS  += \
    powermate.h \
    knobmanager.h \
    knob.h \
    knobbox.h \
    mainwindow.h \
    pv_list.h \
    value_label.h \
    config_list.h

FORMS    +=

INCLUDEPATH += qeframework/include
LIBS += -Lqeframework/lib/linux-x86_64 -lQEFramework
