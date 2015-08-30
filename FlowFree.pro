#-------------------------------------------------
#
# Project created by QtCreator 2015-08-25T14:14:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT      += multimedia

TARGET = FlowFree
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gamesection.cpp \
    gamebody.cpp \
    selectsectiondialog.cpp

HEADERS  += mainwindow.h \
    gamesection.h \
    gamebody.h \
    selectsectiondialog.h

FORMS    += mainwindow.ui \
    selectsectiondialog.ui

RESOURCES += \
    flowfree_resources.qrc
