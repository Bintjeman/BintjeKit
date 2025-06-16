cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
target_sources(bintjekit PRIVATE
        default_event_manager.cpp
        default_core_event_handler.cpp
        i_core_event_handler.cpp
        i_event_manager.cpp
        i_event_listener.cpp

)