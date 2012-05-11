### eqmake4 was here ###
CONFIG -= debug_and_release debug
CONFIG += release

CONFIG      += designer plugin
TARGET      = $$qtLibraryTarget(motorcontroldesignerplugin)
TEMPLATE    = lib

INCLUDEPATH += ../qcamotor ../qcamotorgui ../motorstack
LIBS += -L../qcamotor -lqcamotor \
    -L../qcamotorgui -lqcamotorgui \
    -L../motorstack -lmotorstack

HEADERS     = qcamotordesignerplugin.h motorstackdesignerplugin.h motorcontroldesigner.h
SOURCES     = qcamotordesignerplugin.cpp motorstackdesignerplugin.cpp motorcontroldesigner.cpp
RESOURCES   = icons.qrc
LIBS        += -L.

#target.path = $$[QT_INSTALL_PLUGINS]/designer
#INSTALLS    += target

include(motorstackdesigner.pri)
include(qcamotordesigner.pri)
