################################################################################
###
### @file makelib.cmake
### path 
### project sfml3Test
### @author bintjeman
### @date 30.11.24
###
################################################################################
message("CMAKE_CURRENT_LIST_FILE is ${CMAKE_CURRENT_LIST_FILE}")
################################################################################
# MyLibrarySetup.cmake
include(CMakePackageConfigHelpers)
#include(GNUInstallDirs)

function(add_bnj_library LIB_NAME LIBNAME_FOLDER CXX_MODULES SOURCES HEADERS)
    message("add_bnj_library: ${LIB_NAME} depuis ${LIBNAME_FOLDER}")
    message("Modules ${CXX_MODULES}")
    message("Sources ${SOURCES}")
    message("Headers ${HEADERS}")
    # Créer et installer les fichiers de configuration version
    write_basic_package_version_file(
            "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}ConfigVersion.cmake"
            VERSION ${version}
            COMPATIBILITY AnyNewerVersion
    )

    configure_file(
            cmake/${LIB_NAME}Config.cmake.in
            "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}Config.cmake"
            @ONLY
    )

    # Installer la cible de la bibliothèque
    install(TARGETS ${LIB_NAME}
            EXPORT ${LIB_NAME}Targets
            DESTINATION ${CMAKE_INSTALL_LIBDIR}
            FILE_SET CXX_MODULES
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${LIB_NAME}/src
            FILE_SET HEADERS
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${LIB_NAME}
            INCLUDES
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
    install(
            EXPORT bintjeKitTargets        # Utiliser un nom cohérent avec votre lib
            NAMESPACE bintjeKit::          # Préfixe pour les cibles exportées
            DESTINATION lib/cmake/bintjeKit # Emplacement standard pour les fichiers CMake
            FILE bintjeKitTargets.cmake    # Nom du fichier Targets.cmake
    )
    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}Config.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}ConfigVersion.cmake"
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${LIB_NAME}"  # Dossier attendu par FindPackage
    )
endfunction()
################################################################################
#######