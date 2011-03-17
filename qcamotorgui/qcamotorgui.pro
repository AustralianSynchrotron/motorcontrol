# -------------------------------------------------
# Project created by QtCreator 2009-10-27T18:48:44
# -------------------------------------------------
TARGET = qcamotorgui
TEMPLATE = lib
SOURCES += qcamotorgui.cpp \
    qcamotorgui-additional.cpp
HEADERS += qcamotorgui.h \
    qcamotorgui-additional.h
INCLUDEPATH += ../qcamotor
FORMS += qcamotorgui.ui \
    qcamotorgui-setup.ui \
    qcamotorgui-relative.ui \
    qcamotorgui-pv.ui
LIBS += -L../qcamotor \
    -lqcamotor
headers.files = qcamotorgui.h \
    qcamotorgui-additional.h \
    ui_qcamotorgui.h \
    ui_qcamotorgui-relative.h \
    ui_qcamotorgui-pv.h \
    ui_qcamotorgui-setup.h
headers.path = $$[INSTALLBASE]/include
INSTALLS += headers
target.files = $$[TARGET]
target.path = $$[INSTALLBASE]/lib
INSTALLS += target