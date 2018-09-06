#-------------------------------------------------
#
# Project created by QtCreator 2018-03-19T17:39:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WebServiceClient
TEMPLATE = app

include(./src/qtsoap.pri)

SOURCES += main.cpp\
        webserviceclient.cpp

HEADERS  += webserviceclient.h

FORMS    += webserviceclient.ui
