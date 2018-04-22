#-------------------------------------------------
#
# Project created by QtCreator 2018-04-21T20:50:58
#
#-------------------------------------------------

INCLUDEPATH += /usr/include/c++/5.4.0

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = thermo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../../../../qtcustomplot/qcustomplot/qcustomplot.cpp \
    exchange/exchange.cpp

HEADERS  += mainwindow.h \
    ../../../../qtcustomplot/qcustomplot/qcustomplot.h \
    ../../../../workspace_v7/freertos_demo/exchange/status.h \
    ../../../../workspace_v7/freertos_demo/exchange/Status_t.h \
    links/ComDataReq_t.h \
    links/status.h \
    links/Status_t.h \
    exchange/exchange.h

FORMS    += mainwindow.ui
