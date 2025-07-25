cmake_minimum_required(VERSION 3.31)
include_guard(GLOBAL)
message("Actual *.cmake: ${CMAKE_CURRENT_LIST_FILE}")
################################################################################
if (NOT FROM_CLIONBNJKIT)
    list(PREPEND CMAKE_PREFIX_PATH "$ENV{HOME}/.local")
    list(PREPEND CMAKE_INCLUDE_PATH "$ENV{HOME}/.local/include")
    list(PREPEND CMAKE_LIBRARY_PATH "$ENV{HOME}/.local/lib")
    message(STATUS "CMAKE_PREFIX_PATH = ${CMAKE_PREFIX_PATH}")
    message(STATUS "CMAKE_INCLUDE_PATH = ${CMAKE_INCLUDE_PATH}")
    message(STATUS "CMAKE_LIBRARY_PATH = ${CMAKE_LIBRARY_PATH}")
    ################################################################################
    set(SFML_STATIC_LIBRARIES TRUE)
    set(BUILD_SHARED_LIBS FALSE)
    find_package(SFML 3.0 COMPONENTS System Window Graphics REQUIRED)
    find_package(ImGui-SFML REQUIRED)
    find_package(nlohmann_json REQUIRED)
    find_package(spdlog REQUIRED)
    find_package(EnTT REQUIRED)
    find_package(BintjeKit REQUIRED)
    ################################################################################
else ()
    message("Nous sommes dans clion bintjekit")
endif()
################################################################################
include_directories(/opt/CLI11)
################################################################################