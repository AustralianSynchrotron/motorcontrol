include_directories(../qcamotor)
set(SIP_INCLUDE_DIRS ${PYQT5_SIP_DIR})
separate_arguments(PYQT5_SIP_FLAGS)
set(SIP_EXTRA_OPTIONS ${PYQT5_SIP_FLAGS})

add_sip_python_module(pyqcamotor
  pyqcamotor.sip
  qcamotor
)
