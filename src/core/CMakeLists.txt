cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
add_library(bintjekit_core STATIC
        core.cpp
        core_builder.cpp
        i_module.cpp
)
target_include_directories(bintjekit_core
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
set_target_properties(bintjekit_core PROPERTIES
        VERSION ${PROJECT_VERSION}
        POSITION_INDEPENDENT_CODE ON
)
target_link_libraries(bintjekit_core
        PUBLIC
        SFML::Window
        SFML::System
        SFML::Graphics
)
add_library(BintjeKit::Core ALIAS bintjekit_core)