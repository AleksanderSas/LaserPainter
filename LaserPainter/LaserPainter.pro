#-------------------------------------------------
#
# Project created by QtCreator 2021-01-31T19:25:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

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
    Collection/project.cpp \
        main.cpp \
    hardwareconnector.cpp \
    configuration.cpp \
    Collection/shapecollection.cpp \
    Collection/abstractoperation.cpp \
    Collection/moveoperation.cpp \
    Collection/adddeleteoperation.cpp \
    Collection/multiplemoveoperation.cpp \
    Visitors/beziervisitor.cpp \
    Visitors/abstractvisitor.cpp \
    Visitors/linevisitor.cpp \
    Visitors/circlevisitor.cpp \
    Visitors/halfcirclevisitor.cpp \
    Ui/mainpanel.cpp \
    Ui/shapedesigner.cpp \
    Ui/unredopanel.cpp \
    Ui/multipleselectionmanager.cpp

HEADERS += \
    Collection/project.h \
    hardwareconnector.h \
    configuration.h \
    Collection/shapecollection.h \
    Collection/structs.h \
    Collection/abstractoperation.h \
    Collection/moveoperation.h \
    Collection/adddeleteoperation.h \
    Collection/multiplemoveoperation.h \
    Visitors/abstractvisitor.h \
    Visitors/beziervisitor.h \
    Visitors/linevisitor.h \
    Visitors/circlevisitor.h \
    Visitors/halfcirclevisitor.h \
    Ui/mainpanel.h \
    Ui/shapedesigner.h \
    Ui/unredopanel.h \
    Ui/multipleselectionmanager.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

r_pi {
unix|win32: LIBS += -lwiringPi
}
