# -------------------------------------------------
# Project created by QtCreator 2009-10-27T18:48:44
# -------------------------------------------------
TARGET = motorstack
TEMPLATE = lib
INCLUDEPATH += ../qcamotor ../qcamotorgui
FORMS += motorstack.ui
HEADERS += qmotorstack.h
SOURCES += qmotorstack.cpp
LIBS += -L../qcamotor -L../qcamotorgui \
    -lqcamotor -lqcamotorgui

headers.files = $$HEADERS
headers.path = $$[INSTALLBASE]/include
INSTALLS += headers
target.files = $$[TARGET]
target.path = $$[INSTALLBASE]/lib
INSTALLS += target
