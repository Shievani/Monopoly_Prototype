#-------------------------------------------------
#
# Project created by QtCreator 2015-03-29T00:35:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TrialM
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    monopoly.cpp \
    details.cpp

HEADERS  += mainwindow.h \
    monopoly.h \
    details.h

FORMS    += mainwindow.ui \
    details.ui

RESOURCES += \
    resources.qrc
