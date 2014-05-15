#-------------------------------------------------
#
# Project created by QtCreator 2014-05-14T04:17:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = withUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    BF_debug_interp.cpp

HEADERS  += mainwindow.h \
    BF_debug_interp.h

FORMS    += mainwindow.ui

RESOURCES += \
    mainwindow.qrc
