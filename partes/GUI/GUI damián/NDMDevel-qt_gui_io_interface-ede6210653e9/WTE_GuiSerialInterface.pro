QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17
#DEFINES += QCUSTOMPLOT_USE_LIBRARY

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    jsoncpp/json_reader.cpp \
    jsoncpp/json_value.cpp \
    jsoncpp/json_writer.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    jsoncpp/json/allocator.h \
    jsoncpp/json/assertions.h \
    jsoncpp/json/config.h \
    jsoncpp/json/forwards.h \
    jsoncpp/json/json.h \
    jsoncpp/json/json_features.h \
    jsoncpp/json/reader.h \
    jsoncpp/json/value.h \
    jsoncpp/json/version.h \
    jsoncpp/json/writer.h \
    jsoncpp/json_tool.h \
    jsoncpp/json_valueiterator.inl \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += "./jsoncpp"
#INCLUDEPATH += "C:/QCustomPlotLibs"
#LIBS += -L"C:/QCustomPlotLibs" -L$$PWD -lqcustomplot2

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

