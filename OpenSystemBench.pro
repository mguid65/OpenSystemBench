#-------------------------------------------------
# Project created by QtCreator 2018-02-02T10:49:05
# Matthew Guidry, Scott Wilder 2018
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenSystemBench
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        guisource/configwindow.cpp \
    guisource/runningwindow.cpp \
    guisource/resultwindow.cpp \
    Algorithms/algorithm.cpp \
    Algorithms/nbody.cpp \
    benchbuilder.cpp \
    guisource/runninglog.cpp \
    guisource/thread.cpp \
    guisource/nooptionsselected.cpp \
    Algorithms/pidigits.cpp \
    Algorithms/mandelbrot.cpp \
    Algorithms/spectral-norm.cpp

HEADERS += \
        headers/configwindow.h \
    headers/runninglog.h \
    headers/runningwindow.h \
    headers/resultwindow.h \
    Algorithms/headers/algorithm.h \
    Algorithms/headers/algorithminterface.h \
    benchbuilder.h \
    headers/thread.h \
    headers/nooptionsselected.h \
    Algorithms/headers/abstract.h

FORMS += \
        guistructure/configwindow.ui \
    guistructure/runningwindow.ui \
    guistructure/resultwindow.ui \
    guistructure/nooptionsselected.ui

INCLUDEPATH += \
        headers/

LIBS        += -L$$GMP_PREFIX/lib -lgmpxx -lgmp -lgomp

CONFIG      += static

QMAKE_CXXFLAGS += -fopenmp
