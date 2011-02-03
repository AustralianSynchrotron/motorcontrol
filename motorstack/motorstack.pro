# -------------------------------------------------
# Project created by QtCreator 2009-10-27T18:48:44
# -------------------------------------------------
TARGET = motorstack
TEMPLATE = lib
INCLUDEPATH += ../qcamotor ../qcamotorgui
FORMS += motorstack.ui interbutt.ui
HEADERS += qmotorstack.h interbutt.h
SOURCES += qmotorstack.cpp interbutt.cpp
LIBS += -L../qcamotor -L../qcamotorgui \
    -lqcamotor -lqcamotorgui
headers.files = qmotorstack.h \
    interbutt.h \
    ui_motorstack.h \
    ui_interbut.h
headers.path = $$[INSTALLBASE]/include
INSTALLS += headers
target.files = $$[TARGET]
target.path = $$[INSTALLBASE]/lib
INSTALLS += target
