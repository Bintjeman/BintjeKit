cmake_minimum_required(VERSION 3.31)
include_guard(GLOBAL)
message("Actual *.cmake: ${CMAKE_CURRENT_LIST_FILE}")
################################################################################
# Options
# Modules
option(BINTJEKIT_BUILD_CORE "Build core module" ON)
option(BINTJEKIT_BUILD_WINDOW "Build window module" ON)
option(BINTJEKIT_BUILD_EVENTMANAGER "Build eventmanager module" ON)
option(BINTJEKIT_BUILD_MONOLITHIC "Build monolithic library" ON)
# Tests
option(BINTJEKIT_BUILD_TESTS "Compile tests" ON)
# Examples
option(BINTJEKIT_BUILD_EXAMPLES "Compile examples" ON)
option(BINTJEKIT_BUILD_EXAMPLE_MINIMAL "Compile minimal example" ON)
option(BINTJEKIT_BUILD_EXAMPLE_USER "Compile user_classes example" ON)
if (NOT BINTJEKIT_BUILD_EXAMPLES)
    set(BINTJEKIT_BUILD_EXAMPLE_MINIMAL "Forced OFF - Compile minimal example" OFF)
    set(BINTJEKIT_BUILD_EXAMPLE_USER "Forced OFF - Compile user_classes example" OFF)
endif ()