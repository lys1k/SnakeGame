QT       += core gui
QT       += gui
greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = QtSnake
TEMPLATE = app

SOURCES += main.cpp\
        apple.cpp \
        bonus.cpp \
        controller.cpp

HEADERS  += \
    apple.h \
    bonus.h \
    controller.h
