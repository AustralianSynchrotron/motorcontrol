cmake_minimum_required(VERSION 3.0)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)


project(motorcontrol)
set(VERSION 1.0)

set(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON)

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

find_package(Python3 MODULE COMPONENTS Interpreter Development)
find_package(PyQt5)
find_package(SIP)
if(POLICY CMP0071)
  cmake_policy(SET CMP0071 OLD) # use MACOSX_RPATH
endif()
if (Python3_FOUND AND PYQT5_FOUND AND SIP_EXECUTABLE AND SIP_INCLUDE_DIRS)
  include_directories(${SIP_INCLUDE_DIRS})
  set(SIP_INCLUDE_DIRS ${PYQT5_SIP_DIR})
  separate_arguments(PYQT5_SIP_FLAGS)
  set(SIP_EXTRA_OPTIONS ${PYQT5_SIP_FLAGS})

  add_subdirectory(qcamotor_py)
  add_subdirectory(qcamotorgui_py)
  add_subdirectory(qmotorstack_py)
else()
  message(WARNING "Python modules will not be built: SIP is missing.")
endif()


