cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(Azathoth)
add_subdirectory(Azathothpp)
add_subdirectory(Sandbox)
add_subdirectory(Contrib/glad)




#TOOLS
#set(SOURCES_OBJ2APS tools/converter/obj2aps2/objparser.cpp tools/converter/obj2aps2/obj2aps.cpp Azathoth/src/strutils.cpp)
#add_executable(obj2aps ${SOURCES_OBJ2APS} Azathoth/src/aps.cpp)

#set(SOURCES_MTL2AMS tools/converter/mtl2ams1/mtl2ams.cpp Azathoth/src/strutils.cpp)
#add_executable(mtl2ams ${SOURCES_MTL2AMS} Azathoth/src/ams.cpp)
