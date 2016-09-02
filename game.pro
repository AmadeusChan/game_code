#-------------------------------------------------
#
# Project created by QtCreator 2016-09-01T10:28:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mynetwork.cpp \
    mygame.cpp

HEADERS  += mainwindow.h \
    mynetwork.h \
    abstractgame.h \
    mygame.h

FORMS    += mainwindow.ui

QT += network
