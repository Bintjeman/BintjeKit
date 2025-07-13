cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
target_sources(bintjekit PRIVATE
        default_renderer.cpp
        i_render_system.cpp
        i_bnjkit_imgui.cpp
        i_engine_renderer.cpp
        i_renderer.cpp
        i_bnjkit_imgui.cpp
)