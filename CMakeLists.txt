cmake_minimum_required(VERSION 3.6)
project(azathoth)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB_RECURSE SOURCES_FULL "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES_FULL})
target_link_libraries(${PROJECT_NAME} glfw GLEW GL)

