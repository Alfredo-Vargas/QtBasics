QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = L2calculator
TEMPLATE = app
SOURCES += main.cpp \
    calculatorinterface.cpp \
    calculator.cpp
HEADERS += calculatorinterface.h \
    calculator.h
FORMS += calculatorinterface.ui
