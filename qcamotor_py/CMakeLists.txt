
Python3_add_library(pyqcamotor MODULE
  qcamotor.sip
  sipAPIqcamotor.h
  sipqcamotorcmodule.cpp
  sipqcamotorQCaMotor.cpp
)

target_include_directories(pyqcamotor
  PRIVATE ../qcamotor
)

install(TARGETS pyqcamotor
    DESTINATION ${Python3_SITEARCH}
)
