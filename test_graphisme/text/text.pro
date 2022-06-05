QMAKE_CXXFLAGS += -std=c++11

TARGET = projet_text

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    *.cc \

HEADERS += \
    *.h \
