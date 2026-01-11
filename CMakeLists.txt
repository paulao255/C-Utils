cmake_minimum_required(VERSION 4.2.1)
project(C-Utils VERSION 1.7.0 LANGUAGES C)

# ===== Interface Library =====
add_library(C-Utils INTERFACE)

# ===== Include Path =====
target_include_directories(C-Utils INTERFACE $<INSTALL_INTERFACE:include> $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/C-Utils>)

# ===== Export the package =====
include(CMakePackageConfigHelpers)
export(PACKAGE C-Utils)

# ===== Install Headers =====
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/C-Utils/ DESTINATION include/C-Utils)
# ===== Install the Interface Library & Export =====
install(TARGETS C-Utils EXPORT C-UtilsTargets INCLUDES DESTINATION include)
install(EXPORT C-UtilsTargets FILE C-UtilsTargets.cmake NAMESPACE C-Utils:: DESTINATION lib/cmake/C-Utils)

# ===== Install Config File =====
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/cmake/C-UtilsConfig.cmake DESTINATION lib/cmake/C-Utils)
