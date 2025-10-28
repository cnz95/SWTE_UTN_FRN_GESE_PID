TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Serial/Serial.cpp \
        Serial/serialib.cpp \
        io/control_io.cpp \
        io/gui_io.cpp \
        main.cpp

HEADERS += \
    Serial/Serial.h \
    Serial/serialib.h \
    io/control_io.h \
    io/gui_io.h
