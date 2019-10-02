
Python3_add_library(pyqcamotorgui MODULE
  qcamotorgui.sip
  sipAPIqcamotorgui.h
  sipqcamotorguicmodule.cpp
  sipqcamotorguiQCaMotorGUI.cpp
)

target_include_directories(pyqcamotorgui
  PRIVATE ../qcamotor
  PRIVATE ../qcamotorgui
)

install(TARGETS pyqcamotorgui
    DESTINATION ${Python3_SITEARCH}
)
