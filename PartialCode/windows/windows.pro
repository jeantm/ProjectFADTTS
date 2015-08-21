#-------------------------------------------------
#
# Project created by QtCreator 2015-08-18T10:33:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = windows
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    setinput.cpp \
    info.cpp

HEADERS  += mainwindow.h \
    setinput.h \
    info.h \
    file.h

FORMS    += mainwindow.ui \
    setinput.ui \
    info.ui
