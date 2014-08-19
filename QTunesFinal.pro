#-------------------------------------------------
#
# Project created by QtCreator 2013-03-14T17:27:03
#
#-------------------------------------------------

QT       += core gui widgets
QT       += opengl multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtunesPrototype
TEMPLATE = app


QT += opengl
SOURCES += main.cpp\
        mainwindow.cpp GLWidget.cpp

HEADERS  += mainwindow.h audiere.h GLWidget.h

FORMS    += mainwindow.ui

LIBS += C:/Qt/Qt5.0.0.2/5.0.2/QTunesFinal/audiere.a

CONFIG += debug_and_release

INCLUDEPATH += C:/Qt/Qt5.0.0.2/5.0.2/QTunesFinal/
DEPENDPATH += $$PWD/
