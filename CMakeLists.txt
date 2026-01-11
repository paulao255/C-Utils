cmake_minimum_required(VERSION 3.14)
project(C-Utils VERSION 1.7.0 LANGUAGES C)

add_library(C-Utils INTERFACE)

target_include_directories(
    C-Utils
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/C-Utils>
)

include(CMakePackageConfigHelpers)
export(PACKAGE C-Utils)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/C-Utils/
    DESTINATION include/C-Utils
)

install(
    TARGETS C-Utils
    EXPORT C-UtilsTargets
    INCLUDES DESTINATION include
)

install(
    EXPORT C-UtilsTargets
    FILE C-UtilsTargets.cmake
    NAMESPACE C-Utils::
    DESTINATION lib/cmake/C-Utils
)

install(
    FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/C-UtilsConfig.cmake
    DESTINATION lib/cmake/C-Utils
)

