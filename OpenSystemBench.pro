#-------------------------------------------------
# Project created by QtCreator 2018-02-02T10:49:05
# Matthew Guidry, Scott Wilder 2018
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenSystemBench
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR = ../OpenSystemBench/bin
OBJECTS_DIR = ../OpenSystemBench/.build
MOC_DIR = ../OpenSystemBench/.build
UI_DIR = ../OpenSystemBench/.build

# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    guisource/configwindow.cpp \
    guisource/runningwindow.cpp \
    guisource/resultwindow.cpp \
    Algorithms/algorithm.cpp \
    Algorithms/nbody.cpp \
    guisource/benchbuilder.cpp \
    guisource/runninglog.cpp \
    guisource/thread.cpp \
    guisource/nooptionsselected.cpp \
    Algorithms/pidigits.cpp \
    Algorithms/mandelbrot.cpp \
    Algorithms/spectral-norm.cpp \
    Algorithms/binarytrees.cpp \
    guisource/submitwindow.cpp \
    guisource/notstandarderror.cpp \
    client/src/TCPClient.cpp \
    guisource/genericdialog.cpp \
    sysinfo/cpuinfo.cpp \
    guisource/cpulog.cpp

HEADERS += \
    headers/configwindow.h \
    headers/runninglog.h \
    headers/runningwindow.h \
    headers/resultwindow.h \
    Algorithms/headers/algorithm.h \
    Algorithms/headers/algorithminterface.h \
    headers/benchbuilder.h \
    headers/thread.h \
    headers/nooptionsselected.h \
    Algorithms/headers/abstract.h \
    headers/submitwindow.h \
    headers/notstandarderror.h \
    client/src/TCPClient.h \
    headers/logger.h \
    headers/genericdialog.h \
    sysinfo/cpuinfo.h \
    guisource/cpulog.h \
    headers/cpulog.h

FORMS += \
    guistructure/configwindow.ui \
    guistructure/runningwindow.ui \
    guistructure/resultwindow.ui \
    guistructure/nooptionsselected.ui \
    guistructure/submitwindow.ui \
    guistructure/notstandarderror.ui \
    guistructure/genericdialog.ui

INCLUDEPATH += \
    headers/

LIBS        += -L$$GMP_PREFIX/lib -lgomp

CONFIG      += static

QMAKE_CXXFLAGS += -fopenmp -static -std=c++14
