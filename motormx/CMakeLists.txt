
add_executable(motormx
  motormx.h
  motormx.cpp
  motormx.ui
  motormx.qrc
)

target_include_directories(motormx
  PRIVATE ../qmotorstack
  PRIVATE ../qcamotorgui
  PRIVATE ../qcamotor
)

target_compile_options(motormx
  PRIVATE -fPIC
)

target_link_libraries(motormx
  qmotorstack
  Qt5::Widgets
)

configure_file(MotorControl.desktop.in MotorControlTest.desktop)


install(TARGETS motormx
    DESTINATION bin
)

install(FILES MotorControl.png
    DESTINATION share/icons
)

install(FILES MotorControlTest.desktop
    DESTINATION share/applications
)
