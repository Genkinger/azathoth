cmake_minimum_required(VERSION 3.6)

project(azathoth)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

include_directories(inc)

#AZATHOTH
file(GLOB_RECURSE SOURCES_FULL "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES_FULL})
target_link_libraries(${PROJECT_NAME} glfw GLEW GL)

#TOOLS
set(SOURCES_OBJ2APS tools/converter/obj2aps2/objparser.cpp tools/converter/obj2aps2/obj2aps.cpp src/strutils.cpp)
add_executable(obj2aps ${SOURCES_OBJ2APS} src/aps.cpp)

set(SOURCES_MTL2AMS tools/converter/mtl2ams1/mtl2ams.cpp src/strutils.cpp)
add_executable(mtl2ams ${SOURCES_MTL2AMS} src/ams.cpp)

#AZATHOTHPP
add_executable(azathothpp srcpp/AzMain.cpp)