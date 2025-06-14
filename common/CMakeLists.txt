cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
add_library(time OBJECT
        src/time/time.cpp
)
target_include_directories(time
        PUBLIC
        ${CMAKE_SOURCE_DIR}/common/include    # Changé pour utiliser le chemin absolu depuis la racine
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(time PRIVATE SFML::System)