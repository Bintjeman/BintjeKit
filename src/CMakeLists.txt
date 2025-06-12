cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
add_library(bintjekit STATIC)
# Ajouter chaque sous-module
add_subdirectory(core)
add_subdirectory(window)
add_subdirectory(event_manager)
target_include_directories(bintjekit
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
target_link_libraries(bintjekit
        PUBLIC
        SFML::Window
        SFML::System
        SFML::Graphics
)
set_target_properties(bintjekit PROPERTIES
        VERSION ${PROJECT_VERSION}
        POSITION_INDEPENDENT_CODE ON
)
add_library(BintjeKit::BintjeKit ALIAS bintjekit)