#-------------------------------------------------
#
# Project created by QtCreator 2017-10-30T17:41:32
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NFLTour
TEMPLATE = app
CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    admin.cpp \
    adminlogin.cpp \
    delegate.cpp \
    graph.cpp \
    tour.cpp \
    showtour.cpp \
    adminextraspopup.cpp \
    userdescription.cpp

HEADERS  += mainwindow.h \
    database.h \
    admin.h \
    adminlogin.h \
    delegate.h \
    tour.h \
    graph.h \
    showtour.h \
    adminextraspopup.h \
    userdescription.h \
    map.h

FORMS    += mainwindow.ui \
    admin.ui \
    adminlogin.ui \
    tour.ui \
    showtour.ui \
    adminextraspopup.ui \
    userdescription.ui

RESOURCES += \
    res.qrc
