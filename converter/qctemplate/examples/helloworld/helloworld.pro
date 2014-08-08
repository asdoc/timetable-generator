TARGET = helloworld
TEMPLATE  = app
CONFIG += console

INCLUDEPATH += ../../src/
DEPENDPATH += ../../src/

win32 {
    LIBS += qctemplate.lib
    
    CONFIG(debug, debug|release) {
        QMAKE_LIBDIR += ../../src/debug
    }
    CONFIG(release, debug|release) {
        QMAKE_LIBDIR += ../../src/release    
    }
}

linux-g++ {
    LIBS += -lqctemplate
    QMAKE_LIBDIR += ../../src/
}

SOURCES = main.cpp
