TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG += qt


DEFINES += ZMQ_STATIC
LIBS += -L$$PWD/../lib -lzmq -lws2_32 -lIphlpapi
INCLUDEPATH += $$PWD/../include

SOURCES += \
        main.cpp \
        zmqbroker.cpp

HEADERS += \
    zmqbroker.h
