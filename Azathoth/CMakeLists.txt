project(Azathoth)

include_directories(include)
file(GLOB_RECURSE SOURCES_FULL "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES_FULL})
target_link_libraries(${PROJECT_NAME} glfw GLEW GL)