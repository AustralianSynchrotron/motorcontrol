# -------------------------------------------------
# Project created by QtCreator 2009-10-27T18:48:44
# -------------------------------------------------

TEMPLATE = lib

QT -= gui 

TARGET = qcamotor

INCLUDEPATH += .

DEFINES += CAMOTOR_LIBRARY

SOURCES += qcamotor.cpp 

HEADERS += qcamotor.h

LIBS += -lqepicspv



headers.files = $$HEADERS
headers.path = $$[INSTALLBASE]/include
INSTALLS += headers

target.files = $$[TARGET]
target.path = $$[INSTALLBASE]/lib
INSTALLS += target
