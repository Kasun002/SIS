#-------------------------------------------------
#
# Project created by QtCreator 2015-05-09T20:42:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SIS_final
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    registeruser.cpp \
    newshipdetect.cpp \
    controller.cpp

HEADERS  += mainwindow.h \
    registeruser.h \
    newshipdetect.h \
    controller.h

FORMS    += mainwindow.ui \
    registeruser.ui \
    newshipdetect.ui \
    controller.ui
