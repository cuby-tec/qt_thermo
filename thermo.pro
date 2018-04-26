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
    exchange/exchange.cpp \
    exchange/cnccommand.cpp \
    profiles/profiledialog.cpp \
    profiles/profile.cpp

HEADERS  += mainwindow.h \
    ../../../../qtcustomplot/qcustomplot/qcustomplot.h \
    ../../../../workspace_v7/freertos_demo/exchange/status.h \
    ../../../../workspace_v7/freertos_demo/exchange/Status_t.h \
    links/ComDataReq_t.h \
    links/status.h \
    links/Status_t.h \
    exchange/exchange.h \
    exchange/cnccommand.h \
    profile.h \
    profiles/profiledialog.h \
    profiles/profile.h

FORMS    += mainwindow.ui \
    profiles/profiledialog.ui

RESOURCES += \
    resources.qrc
