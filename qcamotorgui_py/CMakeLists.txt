
if (SIP_EXECUTABLE)

  list(APPEND SIP_INCLUDE_DIRS ${PYQT5_SIP_DIR})
  list(APPEND SIP_INCLUDE_DIRS ../qcamotor_py)
  separate_arguments(PYQT5_SIP_FLAGS)
  set(SIP_EXTRA_OPTIONS ${PYQT5_SIP_FLAGS})
  add_sip_python_module(pyqcamotorgui
    pyqcamotorgui.sip
    qcamotorgui
  )

else()

  Python3_add_library(pyqcamotorgui MODULE
    sipAPIpyqcamotorgui.h
    sippyqcamotorguicmodule.cpp
    sippyqcamotorguiQCaMotorGUI.cpp
  )

  target_include_directories(pyqcamotorgui
    PRIVATE ../qcamotor
    PRIVATE ../qcamotorgui
  )

  target_link_libraries(pyqcamotorgui
    PRIVATE qcamotorgui
    PRIVATE Qt5::Widgets
  )


  install(TARGETS pyqcamotorgui
      DESTINATION ${Python3_SITEARCH}
  )

endif()
