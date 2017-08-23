#-------------------------------------------------
#
# Project created by QtCreator 2017-06-26T15:53:23
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BrickBeaten
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    rect.cpp \
    ball.cpp \
    brick.cpp \
    slider.cpp \
    control.cpp \
    page.cpp

HEADERS  += mainwindow.h \
    rect.h \
    ball.h \
    brick.h \
    slider.h \
    control.h \
    page.h

FORMS    += mainwindow.ui \
    page.ui

RESOURCES += \
    image.qrc \
    sucai.qrc
