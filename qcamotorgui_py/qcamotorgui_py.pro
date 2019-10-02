# -------------------------------------------------
# Project created by QtCreator 2009-10-27T18:48:44
# -------------------------------------------------

TEMPLATE = lib
QT += widgets
TARGET = pyqcamotorgui
CONFIG += plugin no_plugin_name_prefix
QMAKE_EXTENSION_SHLIB = so

INCLUDEPATH += ../qcamotorgui ../qcamotor
OTHER_FILES += qcamotorgui.sip

# files were generated with following command:
# sip -c .  -I /usr/share/sip/PyQt5 -I ../qcamotor_py -n sip -t WS_X11 -t Qt_5 qcamotorgui.sip
SOURCES += sipqcamotorguicmodule.cpp  sipqcamotorguiQCaMotorGui.cpp
HEADERS += sipAPIqcamotorgui.h

LIBS += -L../qcamotorgui -lqcamotorgui -lqtpvwidgets

QMAKE_CXXFLAGS += $$system(python3-config  --includes)

#headers.files = $$HEADERS
#headers.path = $$[INSTALLBASE]/include
#INSTALLS += headers

INSTALLPATH=$$system(python3 -c \"from distutils.sysconfig import get_python_lib; print\(get_python_lib\(\)\)\")
target.files = $$[TARGET]
target.path = /../../../../../../../../../../../$$INSTALLPATH # This is how I force absolute install path
INSTALLS += target
