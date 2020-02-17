list(APPEND SIP_INCLUDES ../qcamotor_py)
include_directories(../qcamotor)
include_directories(../qcamotorgui)
add_sip_python_module(pyqcamotorgui
  pyqcamotorgui.sip
  qcamotorgui
)

