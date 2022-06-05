QMAKE_CXXFLAGS += -std=c++11

TARGET = ex_05_text

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    *.cc \

HEADERS += \
    *.h \
