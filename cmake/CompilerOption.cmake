cmake_minimum_required(VERSION 3.31)
include_guard(GLOBAL)
message("Actual *.cmake: ${CMAKE_CURRENT_LIST_FILE}")
################################################################################
set(BASE_WARNINGS
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wsign-conversion
        -Wcast-align
        -Wcast-qual
        -Wunused
        -Woverloaded-virtual
        -Wformat=2
)
set(STRICT_WARNINGS
        -Wmisleading-indentation
        -Wconversion
        -Wnull-dereference
        -Wdouble-promotion
        -Wimplicit-fallthrough
        -Wswitch-enum
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wundef

)
set(DEBUG_WARNINGS

        ${BASE_WARNINGS}
        ${STRICT_WARNINGS}
        -Werror
)
set(RELEASE_WARNINGS
        ${BASE_WARNINGS}
)
set(DEBUG_OPTIONS
        -g                     # Informations de debug
        -O0                   # Pas d'optimisation pour un meilleur debugging
        #        -fno-omit-frame-pointer # Garde la frame pointer pour un meilleur debugging
        -fno-inline          # Désactive l' inlining pour un meilleur debugging
        #        -D_GLIBCXX_DEBUG     # Active les vérifications de la STL en debug
)
set(RELEASE_OPTIONS
        -DNDEBUG            # Désactive les assertions
        -O3                 # Optimisation maximale
        -flto=auto              # Link Time Optimization
        #        -march=native      # Optimise pour le CPU actuel
        #        -ffast-math        # Optimisations mathématiques agressives
        #        -fomit-frame-pointer # Supprime frame pointer pour la performance

)
################################################################################
function(configure_target_options target_name)
    if (NOT TARGET ${target_name})
        message(STATUS ">> Skipping target ${target_name} (target does not exist)")
        return()
    endif ()

    # Obtenir la cible réelle si c'est une ALIAS
    get_target_property(ALIASED_TARGET ${target_name} ALIASED_TARGET)
    if (ALIASED_TARGET)
        set(actual_target ${ALIASED_TARGET})
        message(STATUS ">> Using actual target ${actual_target} for alias ${target_name}")
    else ()
        set(actual_target ${target_name})
    endif ()

    # Vérifier le type de cible
    get_target_property(target_type ${actual_target} TYPE)
    message(STATUS ">> Target ${actual_target} is of type ${target_type}")

    cmake_parse_arguments(PARSE_ARGV 1 ARG "WERROR;EXTERNAL" "" "")

    if (target_type STREQUAL "INTERFACE_LIBRARY")
        if (CMAKE_BUILD_TYPE STREQUAL "Release")
            target_compile_options(${actual_target}
                    INTERFACE
                    -flto=auto
            )
            target_link_options(${actual_target}
                    INTERFACE
                    -flto=auto
                    -Wl,--gc-sections
            )
        endif ()
    else ()
        # Options de compilation spécifiques pour les cibles non-externes
        if (NOT ARG_EXTERNAL)
            target_compile_options(${actual_target}
                    PRIVATE
                    $<$<CONFIG:Debug>:${DEBUG_OPTIONS}>
                    $<$<CONFIG:Release>:${RELEASE_OPTIONS}>
                    $<$<CONFIG:Debug>:${DEBUG_WARNINGS}>
                    $<$<CONFIG:Release>:${RELEASE_WARNINGS}>
            )
        endif ()

        # Options LTO appliquées à toutes les cibles en Release
        if (CMAKE_BUILD_TYPE STREQUAL "Release")
            target_compile_options(${actual_target}
                    PRIVATE
                    -flto=auto
            )
            target_link_options(${actual_target}
                    PRIVATE
                    -flto=auto
                    -Wl,--gc-sections
            )
        endif ()
    endif ()

    message(STATUS ">> Configuring target ${target_name} (EXTERNAL = ${ARG_EXTERNAL})")
    get_target_property(_linkopts ${actual_target} LINK_OPTIONS)
    if (_linkopts)
        message(STATUS "   Link options: ${_linkopts}")
    else ()
        message(STATUS "   Link options: none")
    endif ()
endfunction()
################################################################################
