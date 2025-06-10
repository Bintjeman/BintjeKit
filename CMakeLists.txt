cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
# Options
include(cmake/options.cmake)
################################################################################
project(Binjekit
        VERSION 0.0.1
        DESCRIPTION "Bibliothèque utilitaire de Bintjeman"
        LANGUAGES CXX)
################################################################################
# Dependencies
################################################################################
# Common
################################################################################
# BinjeKit
add_subdirectory(src)
################################################################################
# Tests
################################################################################
# Examples
if (BINTJEKIT_BUILD_EXAMPLES)
    message("Build examples")
    add_subdirectory(examples)
endif ()