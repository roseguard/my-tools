QT += core
QT -= gui

TEMPLATE = app
TARGET = xKeyCheckAsync
SOURCES += main.cpp

CONFIG += console c++11
CONFIG -= app_bundle

LIBS += -lX11-xcb
LIBS += -lxcb -lX11

#g++ -std=c++11 main.cpp -lX11-xcb -lxcb -lX11

#QT += core


#CONFIG += console
#CONFIG -= app_bundle

#TEMPLATE = app

#SOURCES += main.cpp

