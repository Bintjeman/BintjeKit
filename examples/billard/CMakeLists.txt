cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
set(EXEC_NAME billard)
add_executable(${EXEC_NAME})
target_sources(${EXEC_NAME} PRIVATE
        src/main.cpp
        src/application.cpp
        src/event/event_manager.cpp
        src/window/window.cpp
        src/engine/billard.cpp
        src/renderer/renderer.cpp
)
target_link_libraries(${EXEC_NAME} PRIVATE
        bintjekit::bintjekit
        EnTT::EnTT
        spdlog::spdlog
)
configure_target_options(${EXEC_NAME})