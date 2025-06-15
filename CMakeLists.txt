cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
# Options
include(cmake/Configure.cmake)
include(cmake/Options.cmake)
include(cmake/CompilerOption.cmake)
################################################################################
project(Binjekit
        VERSION 0.0.1
        DESCRIPTION "Bibliothèque utilitaire de Bintjeman"
        LANGUAGES CXX)
################################################################################
# Dependencies
include(cmake/Dependencies.cmake)
################################################################################
# Common
################################################################################
# BinjeKit
add_subdirectory(common)
add_subdirectory(src)
################################################################################
# Tests
################################################################################
# Examples
if (BINTJEKIT_BUILD_EXAMPLES)
    message("Build examples")
    add_subdirectory(examples)
endif ()