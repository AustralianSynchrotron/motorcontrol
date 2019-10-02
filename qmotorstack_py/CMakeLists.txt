
if (SIP_EXECUTABLE)

  set(SIP_INCLUDE_DIRS ${PYQT5_SIP_DIR})
  list(APPEND SIP_INCLUDE_DIRS ../qcamotor_py)
  list(APPEND SIP_INCLUDE_DIRS ../qcamotorgui_py)
  separate_arguments(PYQT5_SIP_FLAGS)
  set(SIP_EXTRA_OPTIONS ${PYQT5_SIP_FLAGS})
  add_sip_python_module(pyqmotorstack
    pyqmotorstack.sip
    qmotorstack
  )

else()

  Python3_add_library(pyqmotorstack MODULE
    sipAPIpyqmotorstack.h
    sippyqmotorstackcmodule.cpp
    sippyqmotorstackQList0101QCaMotor.cpp
    sippyqmotorstackQList0101QCaMotorGUI.cpp
    sippyqmotorstackQMotorStack.cpp
  )

  target_include_directories(pyqmotorstack
    PRIVATE ../qcamotor
    PRIVATE ../qcamotorgui
    PRIVATE ../qmotorstack
  )

  install(TARGETS pyqmotorstack
      DESTINATION ${Python3_SITEARCH}
  )

endif()
