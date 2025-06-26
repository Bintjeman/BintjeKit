cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
add_executable(minimal_exampleMono src/main.cpp)
target_link_libraries(minimal_exampleMono PRIVATE
        SFML::Window
        SFML::System
        SFML::Graphics
        BintjeKit::BintjeKit
)
configure_target_options(minimal_exampleMono)