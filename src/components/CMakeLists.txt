################################################################################
# CMakeLists.txt
# crée le 05.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
add_subdirectory(ui)
add_subdirectory(window)
add_subdirectory(event)
add_subdirectory(playground)