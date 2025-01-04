cmake_minimum_required(VERSION 3.22)
project(
  glad
  LANGUAGES C
)

set(SOURCES src/glad.c)
add_library(glad ${SOURCES})

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(OPENGL_LIBRARY OpenGL32)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(OPENGL_LIBRARY GL)
endif()

target_link_libraries(glad PUBLIC ${OPENGL_LIBRARY})

target_include_directories(glad PUBLIC include)
