cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
add_executable(example)
target_sources(example PRIVATE
        src/main.cpp
)