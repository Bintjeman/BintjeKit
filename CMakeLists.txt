################################################################################
# 
# crée le 05.01.25
# par bintjeman
################################################################################
cmake_minimum_required(VERSION 3.30)
project(BintjeKit LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
include(cmake/SettingPath.cmake)
# Ajout d'options pour gérer les tests et les exemples
option(BINTJEKIT_BUILD_TESTS "Construire les tests" ON)
option(BINTJEKIT_BUILD_EXAMPLES "Construire les exemples" OFF)

add_subdirectory(src)

if (BINTJEKIT_BUILD_TESTS)
    add_subdirectory(tests)
endif ()
if (BINTJEKIT_BUILD_EXEMPLES)
    add_subdirectory(exemples)
endif ()
# Génération de la documentation via Doxygen (facultative)
find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_custom_target(doc
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs
            COMMENT "Génération de la documentation Doxygen"
            VERBATIM
    )
endif()


include(cmake/StatusMessages.cmake)
