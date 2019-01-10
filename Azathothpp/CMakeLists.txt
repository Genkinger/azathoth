project(Azathothpp)

include_directories(inc)
file(GLOB_RECURSE SOURCES_FULL "src/*.cpp")
add_library(${PROJECT_NAME} SHARED ${SOURCES_FULL})
target_link_libraries(${PROJECT_NAME} glfw GLEW GL)