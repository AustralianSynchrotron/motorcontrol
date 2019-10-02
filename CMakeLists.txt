cmake_minimum_required(VERSION 3.0)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(motorcontrol)
set(VERSION 1.0)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})

find_path(QEPICSPV_INC qtpv.h)
if(NOT QEPICSPV_INC)
  message(FATAL_ERROR ": Can't find folder containing qtpv.h")
endif()
include_directories(${QEPICSPV_INC})


add_subdirectory(qcamotor)
add_subdirectory(qcamotorgui)
add_subdirectory(qmotorstack)
add_subdirectory(motormx)
add_subdirectory(qcamotor_py)
add_subdirectory(qcamotorgui_py)
add_subdirectory(qmotorstack_py)


