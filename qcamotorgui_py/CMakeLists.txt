include_directories(../qcamotorgui)
list(APPEND SIP_INCLUDE_DIRS ../qcamotor_py)
add_sip_python_module(pyqcamotorgui
  pyqcamotorgui.sip
  qcamotorgui
)

