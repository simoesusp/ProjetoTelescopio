#-------------------------------------------------
#
# Project created by QtCreator 2014-09-28T19:19:11
#
#-------------------------------------------------

QT       += core
QT       += widgets
QT       -= gui
QT       += network

TARGET = TelescopeControl
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    stellariumtransceiver.cpp

HEADERS += \
    stellariumtransceiver.h
