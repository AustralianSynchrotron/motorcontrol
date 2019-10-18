include_directories(../qmotorstack)
list(APPEND SIP_INCLUDE_DIRS ../qcamotor_py)
list(APPEND SIP_INCLUDE_DIRS ../qcamotorgui_py)
add_sip_python_module(pyqmotorstack
  pyqmotorstack.sip
  qmotorstack
)

