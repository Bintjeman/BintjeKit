################################################################################
# PATH_SETTINGS
# crée le 05.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
# Remplace `~` par son chemin absolu
set(HOME_DIR $ENV{HOME})
set(LOCAL_INSTALL_PATH "${HOME_DIR}/.local/bnj_install")
list(APPEND CMAKE_LIBRARY_PATH "${LOCAL_INSTALL_PATH}/lib")
list(APPEND CMAKE_PROGRAM_PATH "${LOCAL_INSTALL_PATH}/bin")
list(APPEND CMAKE_INCLUDE_PATH "${LOCAL_INSTALL_PATH}/include")
list(APPEND CMAKE_PREFIX_PATH "${LOCAL_INSTALL_PATH}")
