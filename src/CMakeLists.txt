cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
# Ajouter chaque sous-module
if(BINTJEKIT_BUILD_CORE)
    add_subdirectory(core)
endif ()
if (BINTJEKIT_BUILD_WINDOW)
    add_subdirectory(window)
endif ()
if(BINTJEKIT_BUILD_EVENTMANAGER)
    add_subdirectory(event_manager)
endif ()
# Création de la bibliothèque complète si demandée
if (BINTJEKIT_BUILD_MONOLITHIC)
    add_library(bintjekit STATIC
            $<TARGET_OBJECTS:bintjekit_core>
            $<TARGET_OBJECTS:bintjekit_window>
            $<TARGET_OBJECTS:bintjekit_eventmanager>
    )
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
endif ()