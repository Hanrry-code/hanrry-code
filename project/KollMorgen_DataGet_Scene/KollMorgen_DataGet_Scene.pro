#-------------------------------------------------
#
# Project created by QtCreator 2020-06-04T10:44:35
#
#-------------------------------------------------

QT       += core gui network
QT       += printsupport
QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KollMorgen_DataGet_Scene
TEMPLATE = app




SOURCES += main.cpp\
        main_scene.cpp \
    parametersetting_module_obj.cpp \
    parametersetting_widget.cpp \
    qcustomplot.cpp \
    showchart_module.cpp \
    showchart_module_widget.cpp \
    receive_data_widget.cpp

HEADERS  += main_scene.h \
    globle_definition.h \
    parametersetting_module_obj.h \
    parametersetting_widget.h \
    qcustomplot.h \
    showchart_module.h \
    showchart_module_widget.h \
    receive_data_widget.h

FORMS    += main_scene.ui \
    parametersetting_widget.ui \
    showchart_module_widget.ui \
    receive_data_widget.ui

RESOURCES += \
    res_photo.qrc

DISTFILES += \
    ../build-KollMorgen_DataGet_Scene-Desktop_Qt_5_14_2_MinGW_64_bit-Debug/blackOrange.css
