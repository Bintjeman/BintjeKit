cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
set(EXEC_NAME billard)
add_executable(${EXEC_NAME})
target_sources(${EXEC_NAME} PRIVATE
        src/main.cpp
        src/application.cpp
        # Modules
        src/event/event_manager.cpp
        src/window/window.cpp
        src/engine/billard.cpp
        src/renderer/imgui_renderer.cpp
        src/renderer/renderer.cpp
        # Renders Systems
        src/renderer/ball_renderer.cpp
        src/renderer/background_renderer.cpp
        # Engine
        src/engine/entity/ball_init_system.cpp
        # Prefab
        src/engine/entity/ball_prefab.cpp
        # Components
        src/engine/components/radius_component.cpp
        src/engine/components/velocity_compponent.cpp
        src/engine/components/position_component.cpp
        # Components entities
        src/engine/components/entity.hpp
)
target_link_libraries(${EXEC_NAME} PRIVATE
        bintjekit::bintjekit
        EnTT::EnTT
        spdlog::spdlog
)
target_include_directories(${EXEC_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/examples/billard/src
)
configure_target_options(${EXEC_NAME})
set_target_properties(${EXEC_NAME} PROPERTIES
        DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
)
install(TARGETS
        ${EXEC_NAME}
        RUNTIME DESTINATION bin
)
