################################################################################
# 
# crée le 05.01.25
# par bintjeman
################################################################################
cmake_minimum_required(VERSION 3.30)
project(bintjeKit LANGUAGES CXX VERSION 0.2.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE ON)
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(STATUS "Found ccache: ${CCACHE_PROGRAM}")
    set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()
# Ajout d'options pour gérer les tests et les exemples
option(BINTJEKIT_BUILD_TESTS "Construire les tests" ON)
option(BINTJEKIT_BUILD_EXAMPLES "Construire les exemples" OFF)

add_subdirectory(src)

if (BINTJEKIT_BUILD_TESTS)
    add_subdirectory(tests)
endif ()
if (BINTJEKIT_BUILD_EXEMPLES)
    add_subdirectory(exemples)
endif ()

