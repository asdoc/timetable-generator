#-------------------------------------------------
#
# Project created by QtCreator 2014-07-25T22:12:45
#
#-------------------------------------------------

QT       += core gui
QT       += webkit webkitwidget
QT += network
QT += webkit network

TARGET = converter
TEMPLATE = app

INCLUDEPATH += qctemplate/src/
DEPENDPATH += qctemplate/src/

linux-g++ {
    LIBS += -lqctemplate
    QMAKE_LIBDIR += qctemplate/src/
}



SOURCES += main.cpp\
        mainwindow.cpp \
    ../timetable.cpp \
    timetableform.cpp \
    teacherdialog.cpp

HEADERS  += mainwindow.h \
    ../timetable.h \
    timetableform.h \
    teacherdialog.h

FORMS    += mainwindow.ui \
    timetableform.ui \
    teacherdialog.ui

RESOURCES += \
    timetable_data.qrc
