cmake_minimum_required(VERSION 3.31)
include_guard(GLOBAL)
message("Actual *.cmake: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
# Options
option(BINTJEKIT_BUILD_TESTS "Compile tests" ON)
option(BINTJEKIT_BUILD_EXAMPLES "Compile examples" ON)