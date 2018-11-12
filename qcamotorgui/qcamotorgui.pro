# -------------------------------------------------
# Project created by QtCreator 2009-10-27T18:48:44
# -------------------------------------------------
QT += widgets
TARGET = qcamotorgui
TEMPLATE = lib
SOURCES += qcamotorgui.cpp \
    qcamotorgui-additional.cpp
HEADERS += qcamotorgui.h \
    qcamotorgui-additional.h \
    qcamotorgui-local.h
INCLUDEPATH += ../qcamotor
FORMS += qcamotorgui.ui \
    qcamotorgui-setup.ui \
    qcamotorgui-relative.ui \
    qcamotorgui-pv.ui
LIBS += -L../qcamotor -lqcamotor \
        -lqtpvwidgets

OTHER_FILES += \
    listOfKnownMotorPVs.txt

headers.files = qcamotorgui.h
headers.path = $$[INSTALLBASE]/include
INSTALLS += headers
target.files = $$[TARGET]
target.path = $$[INSTALLBASE]/lib
INSTALLS += target

config.files = $$OTHER_FILES
config.path = /../../../../../../../../../../../etc # This is how I force it to be installed in /etc
INSTALLS += config


