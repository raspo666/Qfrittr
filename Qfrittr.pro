QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): CONFIG += c++11
lessThan(QT_MAJOR_VERSION, 5): QMAKE_CXXFLAGS += -std=c++11

TARGET = Qfrittr
TEMPLATE = app

INCLUDEPATH += ../../
SOURCES += \
        config.cpp \
        getgw.cpp \
        main.cpp \
        mainwindow.cpp \
        qcustomplot.cpp \
        socket.cpp \
        Qfrittr.cpp

HEADERS += \
        config.h \
        mainwindow.h \
        project.h \
        qcustomplot.h \
        Qfrittr.h \
        getgw.h \
        socket.h
        
FORMS += \
        config.ui \
        mainwindow.ui
