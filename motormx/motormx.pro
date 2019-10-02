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

icon.path = $$[INSTALLBASE]/share/icons
icon.files += MotorControl.png

desktop.path = $$[INSTALLBASE]/share/applications
desktop.files += MotorControl.desktop

target.files = $$[TARGET]
target.path = $$[INSTALLBASE]/bin
INSTALLS += target desktop icon

RESOURCES += \
    motormx.qrc
