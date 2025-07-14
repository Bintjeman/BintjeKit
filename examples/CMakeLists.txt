cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
if (BINTJEKIT_BUILD_EXAMPLE_EVOBOT)
    add_subdirectory(evobot)
endif ()