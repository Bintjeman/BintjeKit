################################################################################
# CMakeLists.txt
# crée le 05.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")

add_library(bintjeKit STATIC)
set_target_properties(bintjeKit PROPERTIES EXPORT_NAME bintjeKit)

set(BIK_HEADERS "")
set(BIK_MODULES "")
set(BIK_SOURCES "")

find_package(fmt CONFIG REQUIRED)
set(SPDLOG_BUILD_SHARED=OFF)
find_package(spdlog CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
set(SFML_STATIC_LIBRARIES ON)
find_package(SFML 3 COMPONENTS REQUIRED System Window Graphics)

add_subdirectory(external)
add_subdirectory(tools)

add_subdirectory(components)
add_subdirectory(factory)
add_subdirectory(core)

message("BIK_HEADERS: ${BIK_HEADERS}")
message("BIK_SOURCES: ${BIK_SOURCES}")
message("BIK_MODULES: ${BIK_MODULES}")

set(BIK_HEADERS
        tools/logger/logger_define.hpp
        tools/time/using.hpp
)

target_include_directories(bintjeKit
        PUBLIC
        ${CMAKE_INSTALL_PREFIX}/include
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(bintjeKit
        PRIVATE
        ${BIK_SOURCES}
        ${IMGUI_SOURCES}
        PUBLIC
        FILE_SET CXX_MODULES
        BASE_DIRS
        FILES ${BIK_MODULES} PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
        FILES ${BIK_HEADERS} ${IMGUI_HEADERS}
)

target_compile_features(bintjeKit PRIVATE cxx_std_20)

target_link_libraries(bintjeKit
        PRIVATE sfml-imgui time settings d2
)
target_link_libraries(bintjeKit
        PRIVATE fmt::fmt spdlog::spdlog SFML::Window SFML::Graphics SFML::System nlohmann_json::nlohmann_json
)

# Configuration pour l'installation (exportation des cibles)
include(CMakePackageConfigHelpers)
set(INSTALL_CONFIGDIR lib/cmake)

# Générer un fichier d'exportation pour find_package
install(
        EXPORT bintjeKitTargets
        FILE bintjeKitTargets.cmake
        NAMESPACE bintjeKit::
        DESTINATION ${INSTALL_CONFIGDIR}/bintjeKit
)

# Config.cmake et ConfigVersion.cmake
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/bintjeKitConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)
configure_package_config_file(
        "${CMAKE_SOURCE_DIR}/cmake/bintjeKitConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/bintjeKitConfig.cmake"
        INSTALL_DESTINATION ${INSTALL_CONFIGDIR}/bintjeKit
)
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/bintjeKitConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/bintjeKitConfigVersion.cmake"
        DESTINATION ${INSTALL_CONFIGDIR}/bintjeKit
)

install(TARGETS bintjeKit EXPORT bintjeKitTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_PREFIX}/include/bintjeKit
        FILE_SET CXX_MODULES DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/modules/bintjeKit
)
