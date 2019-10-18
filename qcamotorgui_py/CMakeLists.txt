include_directories(../qcamotorgui)
list(APPEND SIP_INCLUDE_DIRS ${PYQT5_SIP_DIR})
list(APPEND SIP_INCLUDE_DIRS ../qcamotor_py)
separate_arguments(PYQT5_SIP_FLAGS)
set(SIP_EXTRA_OPTIONS ${PYQT5_SIP_FLAGS})

add_sip_python_module(pyqcamotorgui
  pyqcamotorgui.sip
  qcamotorgui
)

