################################################################################
# StatusMessages
# crée le 05.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
include("${CMAKE_CURRENT_LIST_DIR}/Messages.cmake")
if (OUT_FILE)
    message_info("CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
endif ()
################################################################################
# Informations générales du projet
################################################################################
# Informations générales du compilateur C++
message_info("Compilateur C++ : ${CMAKE_CXX_COMPILER}")
message_info("Version du compilateur : ${CMAKE_CXX_COMPILER_VERSION}")
# Standard C++ utilisé pour le projet global (si défini)
message_info("Standard C++ global : ${CMAKE_CXX_STANDARD}")
message_info("Standard C++ requis : ${CMAKE_CXX_STANDARD_REQUIRED}")
# Nom de la bibliothèque standard utilisée (libstdc++, libc++ ou autre)
message_info("Bibliothèque standard C++ utilisée : ${CMAKE_CXX_COMPILER_ID}")
message_info("Système d'exploitation détecté : ${CMAKE_SYSTEM_NAME}")
################################################################################
# Informations liées aux cibles
################################################################################
# Fonction utilitaire pour obtenir les infos d'une cible donnée
function(print_target_info target)
    # Vérifier si la cible existe avant de tenter d'afficher les infos
    if (TARGET ${target})
        message_info("---- Informations pour la cible : ${target} ----")
        # Compilateur C++ spécifique à la cible
        get_target_property(target_compiler ${target} INTERFACE_COMPILE_OPTIONS)
        message_info("Options de compilation : ${target_compiler}")
        # Standard C++ propre à la cible
        get_target_property(target_standard ${target} CXX_STANDARD)
        if (NOT target_standard)
            set(target_standard "Non spécifié (hérite de ${CMAKE_CXX_STANDARD})")
        endif ()
        message_info("C++ utilisé sur cette cible : ${target_standard}")
        # Définitions spécifiques à la cible
        get_target_property(target_defines ${target} COMPILE_DEFINITIONS)
        message_info("Définitions de compilation : ${target_defines}")
        # Drapeaux (flags) ajoutés au compilateur
        get_target_property(target_flags ${target} COMPILE_OPTIONS)
        message_info("Flags CMake pour cette cible : ${target_flags}")
        # Répertoires d'inclusion
        get_target_property(target_includes ${target} INCLUDE_DIRECTORIES)
        message_info("Include directories : ${target_includes}")
    else ()
        message_info( "La cible ${target} n'existe pas.")
    endif ()
endfunction()
################################################################################
function(collect_all_targets)
    set(ALL_TARGETS "")
    # Inspecter tous les sous-répertoires
    get_property(subdirectories DIRECTORY PROPERTY SUBDIRECTORIES)
    foreach(subdir ${subdirectories})
        get_property(targets DIRECTORY ${subdir} PROPERTY BUILDSYSTEM_TARGETS)
        list(APPEND ALL_TARGETS ${targets})
    endforeach()
    # Exporter les cibles vers la portée parent
    set(ALL_TARGETS ${ALL_TARGETS} PARENT_SCOPE)
endfunction()
################################################################################
# Lister toutes les cibles et afficher leurs infos
collect_all_targets()
message_info("Liste des cibles définies :")
get_property(targets DIRECTORY PROPERTY ${ALL_TARGETS})
foreach(target ${ALL_TARGETS})
    print_target_info(${target})
endforeach ()
################################################################################
# Options globales (Compilation et liens)
################################################################################
# Options globales de compilation
message_info("Options globales de compilation : ${CMAKE_CXX_FLAGS}")
message_info("Options globales additionnelles pour Release : ${CMAKE_CXX_FLAGS_RELEASE}")
message_info("Options globales additionnelles pour Debug : ${CMAKE_CXX_FLAGS_DEBUG}")
# Options globales de l'éditeur de lien
message_info("Options globales de lien : ${CMAKE_EXE_LINKER_FLAGS}")