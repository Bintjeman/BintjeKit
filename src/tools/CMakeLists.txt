################################################################################
# CMakeLists.txt
# crée le 15.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
add_subdirectory(settings_manager)
add_subdirectory(time)
add_subdirectory(d2)
add_subdirectory(logger)
