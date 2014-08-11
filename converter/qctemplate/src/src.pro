TARGET	   = qctemplate
TEMPLATE  = lib
CONFIG += staticlib

CTEMPLATE_SRC = ctemplate-2.2/src

win32 {
    # disable "unreferenced formal parameter" warning
    QMAKE_CXXFLAGS_WARN_ON -= -w34100

    INCLUDEPATH += $$CTEMPLATE_SRC/windows    
    INCLUDEPATH += $$CTEMPLATE_SRC
        
    CTEMPLATE_HEADERS_DIR = $$CTEMPLATE_SRC/windows/ctemplate
    
    HEADERS += \
        $$CTEMPLATE_SRC/windows/config.h \
        $$CTEMPLATE_SRC/windows/port.h
    
    SOURCES += \
        $$CTEMPLATE_SRC/windows/port.cc
}

win32:staticlib {
    DEFINES += CTEMPLATE_DLL_DECL=
}

linux-g++ {
    QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter -Wno-sign-compare -Wno-type-limits -fdiagnostics-show-option    

    INCLUDEPATH += $$CTEMPLATE_SRC/linux-g++
    INCLUDEPATH += $$CTEMPLATE_SRC
    
    CTEMPLATE_HEADERS_DIR = $$CTEMPLATE_SRC/ctemplate
    
    HEADERS += $$CTEMPLATE_SRC/linux-g++/config.h 
}

HEADERS += \
    QCTemplate.h \
    $$CTEMPLATE_SRC/base/arena.h \
    $$CTEMPLATE_SRC/htmlparser/htmlparser.h \
    $$CTEMPLATE_SRC/htmlparser/htmlparser_cpp.h \
    $$CTEMPLATE_SRC/htmlparser/jsparser.h \
    $$CTEMPLATE_SRC/base/manual_constructor.h \
    $$CTEMPLATE_SRC/base/mutex.h \
    $$CTEMPLATE_SRC/base/small_map.h \
    $$CTEMPLATE_SRC/htmlparser/statemachine.h

SOURCES += \
    QCTemplate.cpp \
    $$CTEMPLATE_SRC/base\arena.cc \
    $$CTEMPLATE_SRC/htmlparser\htmlparser.cc \
    $$CTEMPLATE_SRC/htmlparser\jsparser.cc \
    $$CTEMPLATE_SRC/per_expand_data.cc \
    $$CTEMPLATE_SRC/htmlparser\statemachine.cc \
    $$CTEMPLATE_SRC/template.cc \
    $$CTEMPLATE_SRC/template_annotator.cc \
    $$CTEMPLATE_SRC/template_dictionary.cc \
    $$CTEMPLATE_SRC/template_modifiers.cc \
    $$CTEMPLATE_SRC/template_namelist.cc \
    $$CTEMPLATE_SRC/template_pathops.cc \
    $$CTEMPLATE_SRC/template_string.cc \
    ctemplate-2.2/src/template_cache.cc

# platform specific headers
HEADERS += \
    $$CTEMPLATE_HEADERS_DIR/per_expand_data.h \
    $$CTEMPLATE_HEADERS_DIR/template.h \
    $$CTEMPLATE_HEADERS_DIR/template_annotator.h \
    $$CTEMPLATE_HEADERS_DIR/template_dictionary.h \
    $$CTEMPLATE_HEADERS_DIR/template_dictionary_interface.h \
    $$CTEMPLATE_HEADERS_DIR/template_emitter.h \
    $$CTEMPLATE_HEADERS_DIR/template_enums.h \
    $$CTEMPLATE_HEADERS_DIR/template_modifiers.h \
    $$CTEMPLATE_HEADERS_DIR/template_namelist.h \
    $$CTEMPLATE_HEADERS_DIR/template_pathops.h \
    $$CTEMPLATE_HEADERS_DIR/template_string.h    

    
