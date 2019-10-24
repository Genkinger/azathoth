project(obj2aps2)

include_directories(include ${CMAKE_SOURCE_DIR}/Azathoth/include)
include_directories()
file(GLOB_RECURSE SOURCES_FULL "src/*.cpp" )
add_executable(obj2aps2 ${SOURCES_FULL} ${CMAKE_SOURCE_DIR}/Azathoth/src/aps.cpp ${CMAKE_SOURCE_DIR}/Azathoth/src/strutils.cpp)
