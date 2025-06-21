cmake_minimum_required(VERSION 3.31)
include_guard(GLOBAL)
message("Actual *.cmake: ${CMAKE_CURRENT_LIST_FILE}")
################################################################################
set(CMAKE_CXX_COMPILER_ID "Clang")
################################################################################
list(APPEND CMAKE_PREFIX_PATH "$ENV{HOME}/.local")
################################################################################
# Juste après le project()
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# Pour forcer l'utilisation de Clang
set(CMAKE_CXX_COMPILER /bin/clang++)
set(CMAKE_C_COMPILER /bin/clang)