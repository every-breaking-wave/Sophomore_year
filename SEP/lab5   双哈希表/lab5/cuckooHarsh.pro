TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        cuckohash.cpp \
        main.cpp

HEADERS += \
    cuckohash.h

DISTFILES += \
    sample.in.in \
    sample.out
