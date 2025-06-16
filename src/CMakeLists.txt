cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
# Ajout des helpers CMake
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
add_library(bintjekit STATIC)
################################################################################
add_subdirectory(window)
add_subdirectory(event_manager)
add_subdirectory(engine)
add_subdirectory(renderer)
add_subdirectory(configuration)
target_include_directories(bintjekit
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/common/include>
        $<INSTALL_INTERFACE:include>
)
################################################################################
target_link_libraries(bintjekit
        PUBLIC
        time
)
target_link_libraries(bintjekit
        PUBLIC
        SFML::Window
        SFML::System
        SFML::Graphics
        ImGui-SFML::ImGui-SFML
        spdlog::spdlog
        nlohmann_json::nlohmann_json
)
################################################################################
set_target_properties(bintjekit PROPERTIES
        VERSION ${PROJECT_VERSION}
        POSITION_INDEPENDENT_CODE ON
)
configure_compiler_options(bintjekit)
enable_lto(bintjekit)
################################################################################
add_library(BintjeKit::BintjeKit ALIAS bintjekit)
################################################################################
# Création du fichier de configuration
message("Search path: ${PROJECT_SOURCE_DIR}/cmake/BintjeKitConfig.cmake.in")
configure_package_config_file(
        ${PROJECT_SOURCE_DIR}/cmake/BintjeKitConfig.cmake.in
        ${PROJECT_BINARY_DIR}/BintjeKitConfig.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BintjeKit
)

# Création du fichier de version
write_basic_package_version_file(
        ${PROJECT_BINARY_DIR}/BintjeKitConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

# Installation des fichiers de configuration
install(FILES
        ${PROJECT_BINARY_DIR}/BintjeKitConfig.cmake
        ${PROJECT_BINARY_DIR}/BintjeKitConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BintjeKit
)
