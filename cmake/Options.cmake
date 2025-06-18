cmake_minimum_required(VERSION 3.31)
include_guard(GLOBAL)
message("Actual *.cmake: ${CMAKE_CURRENT_LIST_FILE}")
################################################################################
# Options
# Modules
# Tests
option(BINTJEKIT_BUILD_TESTS "Compile tests" ON)
option(BINTJEKIT_BUILD_TESTS_TIME "Compile time tests" ON)
if (NOT BINTJEKIT_BUILD_TESTS)
    option(BINTJEKIT_BUILD_TESTS_TIME "Forced OFF : Compile time tests" OFF)
endif()
# Examples
option(BINTJEKIT_BUILD_EXAMPLES "Compile examples" ON)
option(BINTJEKIT_BUILD_EXAMPLE_MINIMAL "Compile minimal example" ON)
option(BINTJEKIT_BUILD_EXAMPLE_USER "Compile user_classes example" ON)
option(BINTJEKIT_BUILD_EXAMPLE_GOL "Compile gol example" ON)
if (NOT BINTJEKIT_BUILD_EXAMPLES)
    set(BINTJEKIT_BUILD_EXAMPLE_MINIMAL "Forced OFF - Compile minimal example" OFF)
    set(BINTJEKIT_BUILD_EXAMPLE_USER "Forced OFF - Compile user_classes example" OFF)
    set(BINTJEKIT_BUILD_EXAMPLE_GOL "Forced OFF - Compile gol example" OFF)
endif ()