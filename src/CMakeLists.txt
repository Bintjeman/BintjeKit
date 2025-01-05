################################################################################
# CMakeLists.txt
# crée le 05.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")

add_library(bintjeKit STATIC)

# Ajout des dépendances aux bibliothèques externes
find_package(fmt CONFIG REQUIRED)
set(SPDLOG_BUILD_SHARED=OFF)
set(CMAKE_PREFIX_PATH "$ENV{HOME}/.local/bnj_install" ${CMAKE_PREFIX_PATH})
find_package(spdlog CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
set(SFML_STATIC_LIBRARIES ON)
find_package(SFML 3 COMPONENTS REQUIRED System Window Graphics)

add_subdirectory(tools)
add_subdirectory(core)
add_subdirectory(factory)
add_subdirectory(components)

target_include_directories(bintjeKit
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(bintjeKit
        PUBLIC fmt::fmt spdlog::spdlog SFML::Window SFML::Graphics SFML::System nlohmann_json::nlohmann_json
)
