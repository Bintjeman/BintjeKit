cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
target_sources(bintjekit PRIVATE
        default_renderer.cpp
        render_system_manager.cpp
        i_render_system.cpp
        i_imgui_renderer.cpp
        i_renderer.cpp
)