file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.c)
# file(GLOB_RECURSE EXAMPLE_SOURCES ${CMAKE_CURRENT_LIST_DIR}/examples/*.c)



add_library(LVGL ${SOURCES})
# add_library(LVGL_EXAMPLE STATIC ${EXAMPLE_SOURCES})

include_directories(${CMAKE_SOURCE_DIR}/examples/inc)
include_directories(${CMAKE_CURRENT_LIST_DIR})

