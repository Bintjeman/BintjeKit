cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
add_executable(minimal_example src/main.cpp)
#target_link_libraries(minimal_example BintjeKit::BintjeKit)
target_link_libraries(minimal_example PRIVATE BintjeKit::Window)
