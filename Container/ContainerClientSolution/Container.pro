#-------------------------------------------------
#
# Project created by QtCreator 2022-04-06T08:34:52
#
#-------------------------------------------------

QT       += core gui xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Container
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        box.cpp \
        code.cpp \
        container.cpp \
        containerfactory.cpp \
        cylinder.cpp \
        main.cpp \
        mainwindow.cpp \
        pallet.cpp \
        serialize.cpp \
        toxml.cpp \
        unallocatedcontainer.cpp \
        unallocatedmemento.cpp

HEADERS += \
        box.h \
        code.h \
        container.h \
        containerfactory.h \
        cylinder.h \
        mainwindow.h \
        pallet.h \
        serialize.h \
        toxml.h \
        unallocatedcontainer.h \
        unallocatedmemento.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
