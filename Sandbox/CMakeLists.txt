project(Sandbox)

include_directories(include ${CMAKE_SOURCE_DIR}/Azathothpp/include ${CMAKE_SOURCE_DIR}/Contrib/glad/include)
file(GLOB_RECURSE SOURCES_FULL "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES_FULL})
target_link_libraries(${PROJECT_NAME} Azathothpp)