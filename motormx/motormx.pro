# -------------------------------------------------
# Project created by QtCreator 2009-10-27T18:48:44
# -------------------------------------------------


QT += widgets

TARGET = motormx

TEMPLATE = app

INCLUDEPATH += ../qcamotor ../qcamotorgui ../qmotorstack

SOURCES += \
    motormx_mainwindow.cpp \
    motormx.cpp

HEADERS += \
    motormx_mainwindow.h

FORMS += \
    motormx_mainwindow.ui

LIBS += \
    -lqtpv \
    -L../qcamotor -lqcamotor \
    -L../qcamotorgui -lqcamotorgui \
    -L../qmotorstack -lqmotorstack 

target.files = $$[TARGET]
target.path = $$[INSTALLBASE]/bin
INSTALLS += target

RESOURCES += \
    motormx.qrc
