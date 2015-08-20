#-------------------------------------------------
#
# Project created by QtCreator 2015-06-11T23:41:36
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = SIS_Project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    controller.cpp \
    change_password.cpp \
    test.cpp \
    registor.cpp \
    register_new.cpp \
    cheack_register_dialogbox.cpp \
    controller_new.cpp \
    map_view.cpp \
    show_image.cpp

HEADERS  += mainwindow.h \
    login.h \
    controller.h \
    change_password.h \
    test.h \
    registor.h \
    register_new.h \
    cheack_register_dialogbox.h \
    controller_new.h \
    map_view.h \
    show_image.h

FORMS    += mainwindow.ui \
    login.ui \
    controller.ui \
    change_password.ui \
    test.ui \
    registor.ui \
    register_new.ui \
    cheack_register_dialogbox.ui \
    controller_new.ui \
    map_view.ui \
    show_image.ui

#default path
#INCLUDEPATH +="/usr/local/include"

#new path set
INCLUDEPATH +=/home/janaka/NCReport2.16.0.x64.Qt4.8.6.eval/include

LIBS += `pkg-config --libs opencv`

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../NCReport2.16.0.x64.Qt4.8.6.eval/lib/release/ -lNCReport
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../NCReport2.16.0.x64.Qt4.8.6.eval/lib/debug/ -lNCReport
else:unix: LIBS += -L$$PWD/../NCReport2.16.0.x64.Qt4.8.6.eval/lib/ -lNCReport

INCLUDEPATH += $$PWD/../NCReport2.16.0.x64.Qt4.8.6.eval/include
DEPENDPATH += $$PWD/../NCReport2.16.0.x64.Qt4.8.6.eval/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../NCReport2.16.0.x64.Qt4.8.6.eval/lib/release/ -lNCReportDebug
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../NCReport2.16.0.x64.Qt4.8.6.eval/lib/debug/ -lNCReportDebug
else:unix: LIBS += -L$$PWD/../NCReport2.16.0.x64.Qt4.8.6.eval/lib/ -lNCReportDebug

INCLUDEPATH += $$PWD/../NCReport2.16.0.x64.Qt4.8.6.eval/include
DEPENDPATH += $$PWD/../NCReport2.16.0.x64.Qt4.8.6.eval/include

RESOURCES += \
    report.qrc
