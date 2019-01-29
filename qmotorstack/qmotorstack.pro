# -------------------------------------------------
# Project created by QtCreator 2009-10-27T18:48:44
# -------------------------------------------------
QT += widgets
TARGET = qmotorstack
TEMPLATE = lib
INCLUDEPATH += ../qcamotor ../qcamotorgui
FORMS += qmotorstack.ui
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
