cmake_minimum_required(VERSION 4.2.3)
project(C-Utils LANGUAGES C CXX VERSION 20260220)
add_library(C-Utils INTERFACE)
target_include_directories(
  C-Utils
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
