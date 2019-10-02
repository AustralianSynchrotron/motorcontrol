
Python3_add_library(pyqmotorstack MODULE
  sipAPIqmotorstack.h
  sipqmotorstackcmodule.cpp
  sipqmotorstackQList0101QCaMotor.cpp
  sipqmotorstackQList0101QCaMotorGUI.cpp
  sipqmotorstackQMotorStack.cpp
)

target_include_directories(pyqmotorstack
  PRIVATE ../qcamotor
  PRIVATE ../qcamotorgui
  PRIVATE ../qmotorstack
)

install(TARGETS pyqmotorstack
    DESTINATION ${Python3_SITEARCH}
)
