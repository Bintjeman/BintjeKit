cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
add_executable(minimal)
target_sources(minimal PRIVATE
        src/main.cpp
)
target_link_libraries(minimal PRIVATE
        bintjekit::bintjekit
#        bintjekit::spdlog
        spdlog::spdlog
)