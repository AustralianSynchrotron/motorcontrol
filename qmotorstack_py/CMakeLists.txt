include_directories(../qmotorstack)
list(APPEND SIP_INCLUDES ../qcamotor_py)
list(APPEND SIP_INCLUDES ../qcamotorgui_py)
add_sip_python_module(pyqmotorstack
  pyqmotorstack.sip
  qmotorstack
)

