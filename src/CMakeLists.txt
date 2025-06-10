cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################

# Ajouter chaque sous-module
if(BINTJEKIT_BUILD_WINDOW)
        add_subdirectory(window)
endif()

# Création de la bibliothèque complète si demandée
if(BINTJEKIT_BUILD_ALL)
    add_library(bintjekit_all STATIC
            $<TARGET_OBJECTS:bintjekit_core>
    )
    add_library(BintjeKit::BintjeKit ALIAS bintjekit_bintjekit)
endif()