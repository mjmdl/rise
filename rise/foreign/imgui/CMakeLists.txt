cmake_minimum_required(VERSION 3.22)
project(
  imgui
  LANGUAGES CXX
)

set(
  SOURCES
  imgui/imgui.cpp
  imgui/imgui_demo.cpp
  imgui/imgui_draw.cpp
  imgui/imgui_tables.cpp
  imgui/imgui_widgets.cpp

  imgui/backends/imgui_impl_glfw.cpp
  imgui/backends/imgui_impl_opengl3.cpp
)
add_library(imgui ${SOURCES})

target_include_directories(imgui PUBLIC imgui imgui/backends)
