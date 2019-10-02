
add_library(qcamotor SHARED
  qcamotor.h
  qcamotor.cpp
)

install(TARGETS qcamotor
    LIBRARY DESTINATION lib
)

target_link_libraries(qcamotor
  qtpv
  Qt5::Core
)

install(FILES qcamotor.h
    DESTINATION include
)
