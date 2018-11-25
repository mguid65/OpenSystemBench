#-------------------------------------------------
# Project created by QtCreator 2018-02-02T10:49:05
# Matthew Guidry, Scott Wilder Jan-May 2018
#
# Matthew Guidry, Nam Vu, Mason Walton, Adam Yu,
# Raphaela Mettig, Benjamin Geiss Aug-Nov 2018
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

# need to replace all error dialogs with genericdialog
SOURCES += \
    guisource/main.cpp \
    guisource/configwindow.cpp \
    guisource/runningwindow.cpp \
    guisource/resultwindow.cpp \
    guisource/benchbuilder.cpp \
    guisource/submitwindow.cpp \
    guisource/runninglog.cpp \
    guisource/thread.cpp \
    guisource/genericdialog.cpp \
    algorithms/algorithm.cpp \
    algorithms/nbody.cpp \
    algorithms/pidigits.cpp \
    algorithms/mandelbrot.cpp \
    algorithms/spectral-norm.cpp \
    algorithms/binarytrees.cpp \
    sysinfo/cpuinfo.cpp

# need to replace all error dialogs with genericdialog
HEADERS += \
    headers/configwindow.h \
    headers/runninglog.h \
    headers/runningwindow.h \
    headers/resultwindow.h \
    headers/benchbuilder.h \
    headers/thread.h \
    headers/submitwindow.h \
    headers/logger.h \
    headers/genericdialog.h \
    headers/submit.h \
    algorithms/headers/algorithm.h \
    algorithms/headers/algorithminterface.h \
    algorithms/headers/abstract.h \
    sysinfo/cpuinfo.h \
    headers/submit.h

FORMS += \
    guistructure/configwindow.ui \
    guistructure/runningwindow.ui \
    guistructure/resultwindow.ui \
    guistructure/submitwindow.ui \
    guistructure/genericdialog.ui

win32 {
    INCLUDEPATH += \
        headers/ \
        curl/include/

    LIBS        += -L$$GMP_PREFIX/lib -L$$PWD/curl/lib/ -lgomp -lcurl  -lwinmm -lws2_32
    CONFIG      += static

    QMAKE_CXXFLAGS += -fopenmp -static -std=c++14 -march=nehalem -DSKIP_PEER_VERIFICATION
}
unix {
    INCLUDEPATH += \
        headers/

    LIBS        += -L$$GMP_PREFIX/lib -lgomp -lcurl

    CONFIG      += static

    QMAKE_CXXFLAGS += -fopenmp -static -std=c++14
}
