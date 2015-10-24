#-------------------------------------------------
#
# Project created by QtCreator 2015-10-24T14:16:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NeuroUI
TEMPLATE = app


SOURCES += main.cpp\
        neuroui.cpp \
    ../../Layer.cpp \
    ../../Net.cpp \
    ../../Neuron.cpp \
    netlearner.cpp

HEADERS  += neuroui.h \
    ../../Layer.h \
    ../../Net.h \
    ../../Neuron.h \
    netlearner.h

FORMS    += neuroui.ui

RESOURCES += \
    icons.qrc
