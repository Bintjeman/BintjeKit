cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
add_library(bintjekit_eventmanager STATIC
        i_event_manager.cpp
        default_event_manager.cpp
)
target_include_directories(bintjekit_eventmanager
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
set_target_properties(bintjekit_eventmanager PROPERTIES
        VERSION ${PROJECT_VERSION}
        POSITION_INDEPENDENT_CODE ON
)
target_link_libraries(bintjekit_eventmanager
        PUBLIC
        SFML::Window
)
add_library(BintjeKit::EventManager ALIAS bintjekit_eventmanager)