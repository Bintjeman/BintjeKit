cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################

# Ajouter chaque sous-module
if (BINTJEKIT_BUILD_WINDOW)
    add_subdirectory(window)
endif ()

# Création de la bibliothèque complète si demandée
if (BINTJEKIT_BUILD_MONOLITHIC)
    add_library(bintjekit STATIC
            $<TARGET_OBJECTS:bintjekit_window>
    )
    target_include_directories(bintjekit
            PUBLIC
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
    )
    set_target_properties(bintjekit PROPERTIES
            VERSION ${PROJECT_VERSION}
            POSITION_INDEPENDENT_CODE ON
    )
    add_library(BintjeKit::BintjeKit ALIAS bintjekit)
endif ()