cmake_minimum_required(VERSION 3.22)
project(
  rise
  VERSION "0.0.1"
  DESCRIPTION "Rise Game Engine"
  LANGUAGES CXX
)

set(
  SOURCES
  source/engine.cpp
  source/imgui_layer.cpp
  source/glfw_input.cpp
  source/glfw_window.cpp
  source/layer.cpp
  source/logger.cpp
)
add_library(rise ${SOURCES})

add_subdirectory(foreign/glad)
add_subdirectory(foreign/glfw)
add_subdirectory(foreign/glm)
add_subdirectory(foreign/imgui)
add_subdirectory(foreign/spdlog)
target_link_libraries(
  rise
  PUBLIC glad
  PUBLIC glfw
  PUBLIC glm
  PUBLIC imgui
  PUBLIC spdlog
)

target_precompile_headers(rise PUBLIC include/rise/pch.hpp)
target_include_directories(
  rise
  PUBLIC include
  PRIVATE include/rise
  PRIVATE source
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(PLATFORM_DEFINITION RISE__PLATFORM_WINDOWS)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(PLATFORM_DEFINITION RISE__PLATFORM_LINUX)
else()
  message(FATAL_ERROR "Target platform is not supported yet.")
endif()

target_compile_definitions(
  rise
  PUBLIC PLATFORM_DEFINITION
  PRIVATE RISE__INTERNAL_COMPILATION
)
