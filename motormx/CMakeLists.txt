
add_executable(motormx
  motormx_mainwindow.h
  motormx_mainwindow.ui
  motormx_mainwindow.cpp
  motormx.cpp
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






install(TARGETS motormx
    DESTINATION bin
)

install(FILES MotorControl.png
    DESTINATION share/icons
)

install(FILES MotorControl.desktop
    DESTINATION share/applications
)
