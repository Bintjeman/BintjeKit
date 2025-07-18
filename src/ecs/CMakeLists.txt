cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
target_sources(bintjekit PRIVATE
#        i_system_manager.cpp
        system/i_system.cpp
        prefab/prefab.cpp
        event/event_manager.cpp
        entity_manager.cpp
)
target_sources(bintjekit
        PRIVATE
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_SOURCE_DIR}/include
        FILES
        ${CMAKE_SOURCE_DIR}/include/bintjekit/ecs/i_system_manager.hpp
)
