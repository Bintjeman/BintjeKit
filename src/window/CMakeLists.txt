cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
add_library(bintjekit_window OBJECT
        i_main_window.cpp
        default_main_window.cpp
)
target_include_directories(bintjekit_window
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
set_target_properties(bintjekit_window PROPERTIES
        VERSION ${PROJECT_VERSION}
        POSITION_INDEPENDENT_CODE ON
)
target_link_libraries(bintjekit_window
        PUBLIC
        BintjeKit::Core
        SFML::Window
        SFML::System
        SFML::Graphics
)
add_library(bintjekit_window_static STATIC
        $<TARGET_OBJECTS:bintjekit_window>
)
target_link_libraries(bintjekit_window_static
        PUBLIC
        bintjekit_window
)
add_library(BintjeKit::Window ALIAS bintjekit_window_static)