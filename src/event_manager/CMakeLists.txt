cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
target_sources(bintjekit PRIVATE
        default_event_manager.cpp
        i_event_manager.cpp
        input_binding_manager.cpp
        event_helper.cpp
)
target_sources(bintjekit
        PRIVATE
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_SOURCE_DIR}/include
        FILES
        ${CMAKE_SOURCE_DIR}/include/bintjekit/event_manager/input_binding_manager.hpp
        ${CMAKE_SOURCE_DIR}/include/bintjekit/event_manager/action.hpp
)