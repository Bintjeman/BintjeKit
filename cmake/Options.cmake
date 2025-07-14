cmake_minimum_required(VERSION 3.31)
include_guard(GLOBAL)
message("Actual *.cmake: ${CMAKE_CURRENT_LIST_FILE}")
################################################################################
# Options
# Modules
# Tests
option(BINTJEKIT_BUILD_TESTS "Compile tests" ON)
option(BINTJEKIT_BUILD_TESTS_TIME "Compile time tests" ON)
option(BINTJEKIT_BUILD_TESTS_CONFIGURATION "Compile configuration tests" ON)
if (NOT BINTJEKIT_BUILD_TESTS)
    option(BINTJEKIT_BUILD_TESTS_TIME "Forced OFF : Compile time tests" OFF)
    option(BINTJEKIT_BUILD_TESTS_CONFIGURATION "Forced OFF : Compile configuration tests" OFF)
endif ()
# Examples
option(BINTJEKIT_BUILD_EXAMPLES "Compile examples" ON)
option(BINTJEKIT_BUILD_EXAMPLE_EVOBOT "Compile evobot examples" ON)
if (NOT BINTJEKIT_BUILD_EXAMPLES)
    set(BINTJEKIT_BUILD_EXAMPLE_EVOBOT "Forced off - compile examples" OFF)
endif ()
# Benchmarks
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    option(BINTJEKIT_BUILD_BENCHMARKS "Compile benchmarks (Forced OFF in Debug)" OFF)
else ()
    option(BINTJEKIT_BUILD_BENCHMARKS "Compile benchmarks" ON)
endif ()
option(BINTJEKIT_BUILD_BENCHMARK_TIME "Compile benchmarks test" ON)
if (NOT BINTJEKIT_BUILD_BENCHMARKS)
    option(BINTJEKIT_BUILD_BENCHMARK_TIME "Forced OFF : Compile benchmark test" OFF)
endif ()
if (CMAKE_BUILD_TYPE STREQUAL "Debug" AND BINTJEKIT_BUILD_BENCHMARKS)
    message(STATUS "Les benchmarks sont désactivés en mode Debug pour des résultats pertinents.")
endif ()
if (BINTJEKIT_BUILD_BENCHMARKS)
    # Ici votre configuration des benchmarks avec nanobench
    if (NOT CMAKE_BUILD_TYPE STREQUAL "Release")
        message(WARNING "Les benchmarks devraient être compilés en Release pour des résultats optimaux !")
    endif ()
endif ()
