#-------------------------------------------------
#
# Project created by QtCreator 2018-02-02T10:49:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenSystemBench
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
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
    Algorithms/pidigits.cpp

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

LIBS        += -L$$GMP_PREFIX/lib -lgmpxx -lgmp
