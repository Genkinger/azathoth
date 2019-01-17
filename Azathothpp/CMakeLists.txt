project(Azathothpp)

include_directories(include ${CMAKE_SOURCE_DIR}/Contrib/glad/include)

file(GLOB_RECURSE SOURCES_FULL "src/*.cpp")
add_library(${PROJECT_NAME} SHARED ${SOURCES_FULL})
target_link_libraries(${PROJECT_NAME} glfw glad GL)