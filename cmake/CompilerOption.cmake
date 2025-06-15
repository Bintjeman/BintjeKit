cmake_minimum_required(VERSION 3.31)
include_guard(GLOBAL)
message("Actual *.cmake: ${CMAKE_CURRENT_LIST_FILE}")
################################################################################
# Fonction pour configurer les options de compilation
function(configure_compiler_options target)
    if (MSVC)
        target_compile_options(${target} PRIVATE
                /W4             # Niveau d'avertissement élevé
                /WX            # Traiter les warnings comme des erreurs
                /permissive-   # Standards conformance
                /Zc:preprocessor # Conformité du préprocesseur C++
                /EHsc          # Exception handling
                $<$<CONFIG:Release>:/O2>  # Optimisation maximale en Release
                $<$<CONFIG:Debug>:/Od>    # Désactive l'optimisation en Debug
        )
    else ()
        target_compile_options(${target} PRIVATE
                -Wall
                -Wextra
                -Wpedantic
                -Werror
                -Wconversion
                -Wsign-conversion
                $<$<CONFIG:Release>:-O3>  # Optimisation aggressive en Release
                $<$<CONFIG:Debug>:-O0>    # Pas d'optimisation en Debug
                $<$<CONFIG:Debug>:-g3>    # Informations de debug maximales
        )
        if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            target_compile_options(${target} PRIVATE
                    -Weverything
                    -Wno-c++98-compat
                    -Wno-c++98-compat-pedantic

            )
        endif ()
    endif ()
    # Options C++ communes
    target_compile_features(${target} PRIVATE cxx_std_20)
    # Définitions conditionnelles
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_definitions(${target} PRIVATE
                DEBUG
                _DEBUG
        )
    else ()
        target_compile_definitions(${target} PRIVATE
                NDEBUG
        )
    endif ()
endfunction()
# Fonction pour activer la compilation avec Link Time Optimization (LTO)
function(enable_lto target)
    if (NOT CMAKE_BUILD_TYPE STREQUAL "Release")
        message(STATUS "LTO désactivé pour ${target} (actif uniquement en Release)")
        return()
    endif ()
    include(CheckIPOSupported)
    check_ipo_supported(RESULT supported OUTPUT error)
    if (supported)
        set_target_properties(${target} PROPERTIES
                INTERPROCEDURAL_OPTIMIZATION TRUE
        )
    else ()
        message(WARNING "LTO n'est pas supporté: ${error}")
    endif ()
endfunction()
function(configure_external_library_options target)
    if (NOT TARGET ${target})
        message(STATUS "La cible ${target} n'existe pas, ignore la configuration")
        return()
    endif ()
    # Vérifier le type de cible
    get_target_property(target_type ${target} TYPE)
    if (target_type STREQUAL "INTERFACE_LIBRARY")
        message(STATUS "La cible ${target} est une bibliothèque d'interface, ignore la configuration")
        return()
    endif ()

    if (MSVC)
        target_compile_options(${target} PRIVATE
                /W0            # Désactive les warnings
                $<$<CONFIG:Release>:/O2>
                $<$<CONFIG:Debug>:/Od>
        )
    else ()
        target_compile_options(${target} PRIVATE
                -w            # Désactive tous les warnings
                $<$<CONFIG:Release>:-O3>
                $<$<CONFIG:Debug>:-O0>
                $<$<CONFIG:Debug>:-g3>
        )
    endif ()
    # Options C++ communes
    target_compile_features(${target} PRIVATE cxx_std_20)
    # Définitions conditionnelles
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_definitions(${target} PRIVATE DEBUG _DEBUG)
    else ()
        target_compile_definitions(${target} PRIVATE NDEBUG)
    endif ()
endfunction()
