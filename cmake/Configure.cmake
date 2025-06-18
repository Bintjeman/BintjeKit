cmake_minimum_required(VERSION 3.31)
include_guard(GLOBAL)
message("Actual *.cmake: ${CMAKE_CURRENT_LIST_FILE}")
################################################################################
set(CMAKE_VERBOSE_MAKEFILE ON)
################################################################################
set(CMAKE_DEBUG_POSTFIX d)
################################################################################
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    message(STATUS "LTO activé (Release)")
endif()
################################################################################