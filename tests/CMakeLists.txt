cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
if (BINTJEKIT_BUILD_TESTS_TIME)
    add_subdirectory(time)
endif ()
if (BINTJEKIT_BUILD_TESTS_CONFIGURATION)
    add_subdirectory(configuration)
endif ()
