cmake_minimum_required(VERSION 3.31)
include_guard(GLOBAL)
message("Actual *.cmake: ${CMAKE_CURRENT_LIST_FILE}")
################################################################################
list(PREPEND CMAKE_PREFIX_PATH "$ENV{HOME}/.local")
message(STATUS "CMAKE_PREFIX_PATH = ${CMAKE_PREFIX_PATH}")
################################################################################
#set(SFML_STATIC_LIBRARIES TRUE)
#set(BUILD_SHARED_LIBS FALSE)
#find_package(BintjeKit REQUIRED)
#find_package(spdlog REQUIRED)
#find_package(OpenGL REQUIRED)
################################################################################
