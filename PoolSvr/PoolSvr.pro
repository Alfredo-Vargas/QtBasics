#-------------------------------------------------
#
# Project created by QtCreator 2013-04-09T01:33:31
#
#-------------------------------------------------

QT       += core
QT       += network

QT       -= gui

TARGET = PoolSvr
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    myserver.cpp \
    myrunnable.cpp

HEADERS += \
    myserver.h \
    myrunnable.h
