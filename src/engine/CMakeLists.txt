cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
target_sources(bintjekit PRIVATE
        world.cpp
        system/i_system.cpp
        prefab/prefab.cpp
        event/event_manager.cpp
        entity_manager.cpp
        i_engine.cpp
        play_ground.cpp
)