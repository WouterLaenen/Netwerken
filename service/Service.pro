TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG += qt


DEFINES += ZMQ_STATIC
LIBS += -L$$PWD/../lib -lzmq -lws2_32 -lIphlpapi
INCLUDEPATH += $$PWD/../include

SOURCES += \
        main.cpp \
        message.cpp \
        task.cpp \
        zmqbroker.cpp

HEADERS += \
    message.h \
    task.h \
    zmqbroker.h
