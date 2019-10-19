
add_library(qcamotorgui SHARED
  qcamotorgui.h
  qcamotorgui-additional.h
  qcamotorgui.cpp
  qcamotorgui-additional.cpp
  qcamotorgui.ui
  qcamotorgui-setup.ui
  qcamotorgui-relative.ui
  qcamotorgui-pv.ui
)

target_include_directories(qcamotorgui
  PUBLIC ../qcamotor
)

target_link_libraries(qcamotorgui
  qcamotor
  qtpvwidgets
)

install(TARGETS qcamotorgui
    LIBRARY DESTINATION lib
)

install(FILES qcamotorgui.h
    DESTINATION include
)

install(FILES listOfKnownMotorPVs.txt
    DESTINATION share
)
