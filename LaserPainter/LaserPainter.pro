#-------------------------------------------------
#
# Project created by QtCreator 2021-01-31T19:25:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LaserPainter
TEMPLATE = app

#comment the line below to compile on desktop
CONFIG += r_pi

r_pi {
DEFINES += R_PI
}

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
        main.cpp \
    bezierdesigner.cpp \
    beziervisitor.cpp \
    mainpanel.cpp \
    hardwareconnector.cpp \
    shapecollection.cpp \
    abstractvisitor.cpp \
    linevisitor.cpp \
    circlevisitor.cpp \
    abstractoperation.cpp \
    moveoperation.cpp \
    adddeleteoperation.cpp \
    configuration.cpp

HEADERS += \
    bezierdesigner.h \
    beziervisitor.h \
    mainpanel.h \
    hardwareconnector.h \
    shapecollection.h \
    abstractvisitor.h \
    structs.h \
    linevisitor.h \
    circlevisitor.h \
    abstractoperation.h \
    moveoperation.h \
    adddeleteoperation.h \
    configuration.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

r_pi {
unix|win32: LIBS += -lwiringPi
}
