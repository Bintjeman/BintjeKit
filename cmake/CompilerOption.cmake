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
#        -fno-inline          # Désactive l' inlining pour un meilleur debugging
#        -D_GLIBCXX_DEBUG     # Active les vérifications de la STL en debug
)
set(RELEASE_OPTIONS
        -DNDEBUG            # Désactive les assertions
        -O3                 # Optimisation maximale
#        -flto              # Link Time Optimization
#        -march=native      # Optimise pour le CPU actuel
#        -ffast-math        # Optimisations mathématiques agressives
#        -fomit-frame-pointer # Supprime frame pointer pour la performance

)
################################################################################
function(configure_target_options target_name)
    cmake_parse_arguments(PARSE_ARGV 1 ARG "WERROR;EXTERNAL" "" "")
    if (NOT ARG_EXTERNAL)
        target_compile_options(${target_name}
                PRIVATE
                $<$<CONFIG:Debug>:${DEBUG_OPTIONS}>
                $<$<CONFIG:Release>:${RELEASE_OPTIONS}>
                $<$<CONFIG:Debug>:${DEBUG_WARNINGS}>
                $<$<CONFIG:Release>:${RELEASE_WARNINGS}>
        )
    endif ()
endfunction()
################################################################################
