# -------------------------------------------------
# Project created by QtCreator 2009-10-27T18:48:44
# -------------------------------------------------

TARGET = motormx

TEMPLATE = app

INCLUDEPATH += ../qcamotor ../qcamotorgui ../motorstack

SOURCES += main.cpp \
    mainwindow.cpp

HEADERS += mainwindow.h

FORMS += mainwindow.ui

LIBS += -L../qcamotor -lqcamotor \
    -L../qcamotorgui -lqcamotorgui \
    -L../motorstack -lmotorstack \

target.files = $$[TARGET]
target.path = $$[INSTALLBASE]/bin
INSTALLS += target

RESOURCES += \
    motormx.qrc
