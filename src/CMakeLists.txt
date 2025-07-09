cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
add_subdirectory(core)
add_subdirectory(window)
add_subdirectory(event_manager)
add_subdirectory(engine)
add_subdirectory(renderer)
add_subdirectory(configuration)
add_subdirectory(entity)
add_subdirectory(logger)
################################################################################