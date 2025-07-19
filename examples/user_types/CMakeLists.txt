cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
set(EXEC_NAME usertypes)
add_executable(${EXEC_NAME})
target_sources(${EXEC_NAME} PRIVATE
        src/main.cpp
        src/event_manager.cpp
        src/im_gui_renderer.cpp
        src/renderer.cpp
        src/window.cpp
        src/engine.cpp
)
target_link_libraries(${EXEC_NAME} PRIVATE
        bintjekit::bintjekit
        EnTT::EnTT
        spdlog::spdlog
)
configure_target_options(${EXEC_NAME})