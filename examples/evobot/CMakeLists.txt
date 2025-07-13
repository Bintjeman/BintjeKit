cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
add_executable(evobot)
target_sources(evobot PRIVATE
        main.cpp
        # applications
        application/application.cpp
        application/event_manager.cpp
        application/window.cpp
        application/defaults_options.cpp
        # renderer
        renderer/imgui_renderer.cpp
        renderer/evobot_renderer.cpp
        renderer/renderer.cpp
        # systems
        evobot_engine/system/movement.cpp
        # components
        # engine
        evobot_engine/evo_world.cpp
        evobot_engine/evobot_engine.cpp
)
target_include_directories(evobot PRIVATE ${PROJECT_SOURCE_DIR}/examples/evobot)
target_link_libraries(evobot PRIVATE
        BintjeKit::BintjeKit
        SFML::Graphics
)