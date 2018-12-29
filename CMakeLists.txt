cmake_minimum_required(VERSION 3.6)

project(azathoth)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

#AZATHOTH
file(GLOB_RECURSE SOURCES_FULL "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES_FULL})
target_link_libraries(${PROJECT_NAME} glfw GLEW GL)

#TOOLS
file(GLOB_RECURSE SOURCES_OBJ2APS "tools/converter/obj2aps2/*.cpp")
add_executable(obj2aps ${SOURCES_OBJ2APS} src/aps.cpp)
#target_link_libraries(obj2aps )