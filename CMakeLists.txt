cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
################################################################################
project(Binjekit
        VERSION 0.0.1
        DESCRIPTION "Bibliothèque utilitaire de Bintjeman"
        LANGUAGES CXX)
################################################################################
# Options
include(cmake/Configure.cmake)
include(cmake/Options.cmake)
include(cmake/CompilerOption.cmake)
################################################################################
# Inclure les helpers CMake nécessaires
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
# Dependencies
include(cmake/Dependencies.cmake)
################################################################################
# Définition de la bibliothèque principale
add_library(bintjekit STATIC)
################################################################################
# Définition des cibles objets (object libraries)
add_library(time OBJECT)
################################################################################
# Ajout des autres cibles (test, examples) pour l'instant définies dans leurs
# propres répertoires
################################################################################
# Ajout des sous répertoires
add_subdirectory(common)
add_subdirectory(src)
################################################################################
target_include_directories(time PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/common/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_features(time PUBLIC cxx_std_20)
target_link_libraries(time PUBLIC SFML::System)
################################################################################
# Ajout des sous-composants à la bibliothèque principale
target_sources(bintjekit
        PRIVATE
        $<TARGET_OBJECTS:time>
)
################################################################################
# Configuration de la bibliothèque principale
target_include_directories(bintjekit
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/common/include>
        $<INSTALL_INTERFACE:include>
)
target_include_directories(bintjekit SYSTEM PUBLIC ${SPDLOG_INCLUDES})

################################################################################
target_link_libraries(bintjekit
        PUBLIC
        SFML::Graphics
        SFML::Window
        SFML::System
        ImGui-SFML::ImGui-SFML
        spdlog::spdlog
        nlohmann_json::nlohmann_json
)
################################################################################
# Configuration des suffixes
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "Suffixe pour les builds debug")
# Appliquer le suffixe à votre bibliothèque
set_target_properties(bintjekit PROPERTIES
        DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}"
)
################################################################################
set_target_properties(bintjekit PROPERTIES
        VERSION ${PROJECT_VERSION}
        POSITION_INDEPENDENT_CODE ON
)
################################################################################
# Configuration des options de compilation
configure_target_options(bintjekit)
################################################################################
# Alias pour la cible
add_library(BintjeKit::BintjeKit ALIAS bintjekit)
################################################################################
set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local")
################################################################################
# Configuration du package
configure_package_config_file(
        ${PROJECT_SOURCE_DIR}/cmake/BintjeKitConfig.cmake.in
        ${PROJECT_BINARY_DIR}/BintjeKitConfig.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BintjeKit
)
write_basic_package_version_file(
        ${PROJECT_BINARY_DIR}/BintjeKitConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)
################################################################################
# Installation
install(FILES
        ${PROJECT_BINARY_DIR}/BintjeKitConfig.cmake
        ${PROJECT_BINARY_DIR}/BintjeKitConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BintjeKit
)
# Installation des headers de la bibliothèque principale
install(
        DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.hpp" PATTERN "*.inl"
)
# Installation des headers communs
install(
        DIRECTORY ${PROJECT_SOURCE_DIR}/common/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.hpp" PATTERN "*.inl"
)
################################################################################
# Installation des cibles et des dépendances
install(TARGETS
        bintjekit
#        bintjekit_compiler_options
        time
        spdlog
        EXPORT BintjeKitTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
################################################################################
install(
        EXPORT BintjeKitTargets
        FILE BintjeKitTargets.cmake
        NAMESPACE BintjeKit::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BintjeKit
)
################################################################################
# Tests, Examples et Benchmarks conditionnels
if (BINTJEKIT_BUILD_TESTS)
    include(cmake/Testing.cmake)
    add_subdirectory(tests)
endif ()

if (BINTJEKIT_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()

if (BINTJEKIT_BUILD_BENCHMARKS)
    include(cmake/Benchmarks.cmake)
    add_subdirectory(benchmarks)
endif ()
