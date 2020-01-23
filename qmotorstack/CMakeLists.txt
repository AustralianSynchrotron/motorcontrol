
set(CMAKE_AUTOUIC_SEARCH_PATHS ../qcamotorgui)

add_library(qmotorstack SHARED
  qmotorstack.ui
  qmotorstack.h
  qmotorstack.cpp
)

target_include_directories(qmotorstack
  PRIVATE ${PROJECT_BINARY_DIR}/qcamotorgui
  PRIVATE ../qcamotorgui 
)

target_link_libraries(qmotorstack
  qcamotorgui
)

install(TARGETS qmotorstack
    LIBRARY DESTINATION lib
)

install(FILES qmotorstack.h
    DESTINATION include
)
