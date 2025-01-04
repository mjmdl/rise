cmake_minimum_required(VERSION 3.22)
project(
  testbed
  VERSION "0.0.1"
  DESCRIPTION "Rise Testbed"
  LANGUAGES CXX
)

set(
  SOURCES
  source/game.cpp
  source/main.cpp
)
add_executable(testbed ${SOURCES})

target_link_libraries(testbed PRIVATE rise)

target_include_directories(
  testbed
  PRIVATE source
)
