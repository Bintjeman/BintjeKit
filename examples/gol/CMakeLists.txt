cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
add_executable(gol
        src/main.cpp
        src/game_of_life.cpp
        src/game_of_life_renderer.cpp
        src/renderer.cpp
)
target_include_directories(gol PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include

)
target_link_libraries(gol PRIVATE
        BintjeKit::BintjeKit
        SFML::Graphics
)