#-------------------------------------------------
#
# Project created by QtCreator 2017-08-09T20:27:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += sql

TARGET = Restaurant
TEMPLATE = app


SOURCES += main.cpp\
    customerwindow.cpp \
    systemmanagerwindow.cpp \
    cookwindow.cpp \
    waiterwindow.cpp \
    managerwindow.cpp \
    waitermsgquery.cpp \
    myquery.cpp \
    waiterlistquery.cpp \
    customerorderquery.cpp \
    inputwindow.cpp \
    loginwindow.cpp \
    registerwindow.cpp

HEADERS  += \
    connection.h \
    pixmapdelegate.h \
    seatiddelegate.h \
    seattakendelegate.h \
    customerwindow.h \
    systemmanagerwindow.h \
    cookwindow.h \
    waiterwindow.h \
    managerwindow.h \
    readonlydelegate.h \
    aligncentermodel.h \
    menuitemwidget.h \
    evaluationitemwidget.h \
    itemwidget.h \
    progressitemwidget.h \
    starsitemwidget.h \
    waiterevaluationwidget.h \
    mypushbutton.h \
    detaildialog.h \
    commentwidget.h \
    waitermsgquery.h \
    myquery.h \
    waiterlistquery.h \
    menuquery.h \
    customerorderquery.h \
    inputwindow.h \
    loginwindow.h \
    registerwindow.h \
    accounsquery.h

FORMS    +=

RESOURCES += \
    image.qrc

RC_ICONS = "Restaurant.ico"

DISTFILES +=
LIBS += -lwsock32
