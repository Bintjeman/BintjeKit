cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
target_sources(bintjekit PRIVATE
        gameplay_system_manager.cpp
        physic_system_manager.cpp
        i_world.cpp
        play_ground.cpp
)