include_directories(../qmotorstack)
set(SIP_INCLUDE_DIRS ${PYQT5_SIP_DIR})
list(APPEND SIP_INCLUDE_DIRS ../qcamotor_py)
list(APPEND SIP_INCLUDE_DIRS ../qcamotorgui_py)
separate_arguments(PYQT5_SIP_FLAGS)
set(SIP_EXTRA_OPTIONS ${PYQT5_SIP_FLAGS})

add_sip_python_module(pyqmotorstack
  pyqmotorstack.sip
  qmotorstack
)

