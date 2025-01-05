################################################################################
# 
# crée le 05.01.25
# par bintjeman
################################################################################
cmake_minimum_required(VERSION 3.30)
project(BintjeKit LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include(cmake/SettingPath.cmake)
# Ajout d'options pour gérer les tests et les exemples
option(BINTJEKIT_BUILD_TESTS "Construire les tests" ON)
option(BINTJEKIT_BUILD_EXAMPLES "Construire les exemples" OFF)

if (BINTJEKIT_BUILD_TESTS)
    add_subdirectory(tests)
endif ()
if (BINTJEKIT_BUILD_EXEMPLES)
    add_subdirectory(exemples)
endif ()