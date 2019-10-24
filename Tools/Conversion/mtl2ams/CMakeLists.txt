project(mtl2ams)

include_directories(${CMAKE_SOURCE_DIR}/Azathoth/include)
file(GLOB_RECURSE SOURCES_FULL "src/*.cpp" )
add_executable(mtl2ams ${SOURCES_FULL} ${CMAKE_SOURCE_DIR}/Azathoth/src/ams.cpp ${CMAKE_SOURCE_DIR}/Azathoth/src/strutils.cpp)
