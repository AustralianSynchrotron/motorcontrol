# -------------------------------------------------
# Project created by QtCreator 2009-10-27T18:48:44
# -------------------------------------------------

TEMPLATE = lib

QT -= gui

TARGET = pqcamotor

INCLUDEPATH += ../qcamotor

OTHER_FILES += pqcamotor.sip

# files were generated with following command:
# sip -c .  -I /usr/share/sip/PyQt5 -n sip -t WS_X11 -t Qt_5 pqcamotor.sip

SOURCES += sipqcamotorcmodule.cpp sipqcamotorQCaMotor.cpp
HEADERS += sipAPIqcamotor.h

LIBS += -L../qcamotor -lqcamotor -lqtpvwidgets

QMAKE_CXXFLAGS += $$system(python-config  --includes)

#headers.files = $$HEADERS
#headers.path = $$[INSTALLBASE]/include
#INSTALLS += headers

INSTALLPATH=$$system(python3 -c \"from distutils.sysconfig import get_python_lib; print\(get_python_lib\(\)\)\")
target.files = $$[TARGET]
target.path = $$INSTALLPATH
INSTALLS += target
