project(glad)

set(CMAKE_C_FLAGS "-fpic")
include_directories(include)
add_library(${PROJECT_NAME} src/glad.c)