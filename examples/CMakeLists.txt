cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
add_subdirectory(minimal)
add_subdirectory(user_types)
add_subdirectory(billard)
add_subdirectory(evobot)