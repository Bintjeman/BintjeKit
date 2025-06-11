cmake_minimum_required(VERSION 3.31)
include_guard(GLOBAL)
message("Actual *.cmake: ${CMAKE_CURRENT_SOURCE_DIR}")
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
