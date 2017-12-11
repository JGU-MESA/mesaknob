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
    value_label.cpp

HEADERS  += \
    powermate.h \
    knobmanager.h \
    knob.h \
    knobbox.h \
    mainwindow.h \
    pv_list.h \
    value_label.h

FORMS    +=

INCLUDEPATH += /epics/epicsqt/qeframework/include
LIBS += -L/epics/epicsqt/qeframework/lib/linux-x86_64 -lQEFramework
