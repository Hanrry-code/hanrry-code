QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    init.cpp \
    main.cpp \
    mythread.cpp \
    widget.cpp

HEADERS += \
    axes.h \
    mythread.h \
    widget.h

INCLUDEPATH    += ../include

DESTDIR = ../bin

win32{
    QMAKE_CXXFLAGS += -MP
    QMAKE_CXXFLAGS += $$QMAKE_CFLAGS_STL

    LIBS += -L../lib -lqwtplot3d -lopengl32 -lglu32 -lgdi32
}

unix:!macx { LIBS += -L../lib -lqwtplot3d -lGLU }

macx: LIBS += -L../lib -lqwtplot3d -framework OpenGL

linux-g++:QMAKE_CXXFLAGS += -fno-exceptions

#RC_FILE = ../icon.rc

#RESOURCES     = ../images.qrc


FORMS += \
    widget.ui

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../data/data.txt

LIBS += ../O/Communicate.o
LIBS += ../O/DivFun.o
LIBS += ../O/JointInterpolation.o
LIBS += ../O/RobotCommunicate.o
LIBS += ../O/RobotErrorPlan.o
LIBS += ../O/RobotInterpolation.o
LIBS += ../O/RobotKinematics.o
LIBS += ../O/RobotMatrix.o
LIBS += ../O/RobotMotionControl.o
LIBS += ../O/RobotPlanning.o
LIBS += ../O/RobotQueue.o
LIBS += ../O/RobotTable.o
LIBS += ../O/RobotTeachPlan.o
LIBS += ../O/RobotVelControl.o
LIBS += ../O/ServoInfo.o
LIBS += ../O/SpeedProcess.o

RESOURCES += \
    qss.qrc

