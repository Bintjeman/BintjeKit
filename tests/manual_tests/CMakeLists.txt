################################################################################
# CMakeLists.txt
# crée le 05.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
OPTION(TEST_MINIMAL "Construit le test minimal" OFF)
OPTION(TEST_CONFIGURATION "Construit le test configuration" OFF)
OPTION(TEST_COMPONANTS "Construit le test componants" OFF)
OPTION(TEST_GOL "Construit le test GOL" ON)
if (TEST_MINIMAL)
    add_subdirectory(minimal)
endif ()
if (TEST_CONFIGURATION)
    add_subdirectory(configuration)
endif ()
if (TEST_COMPONANTS)
    add_subdirectory(componants)
endif ()
if (TEST_GOL)
    add_subdirectory(gol)
endif ()