project(Sandbox)

include_directories(inc ../Azathothpp/inc)
file(GLOB_RECURSE SOURCES_FULL "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES_FULL})
target_link_libraries(${PROJECT_NAME} Azathothpp)