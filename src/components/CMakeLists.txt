################################################################################
# CMakeLists.txt
# crée le 15.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
add_subdirectory(common)
add_subdirectory(imgui_wrapper)
add_subdirectory(playground)
add_subdirectory(renderer)
add_subdirectory(ui)
add_subdirectory(window)
set(BIK_HEADER ${BIK_HEADERS} PARENT_SCOPE)
set(BIK_MODULES ${BIK_MODULES} PARENT_SCOPE)
set(BIK_SOURCES ${BIK_SOURCES} PARENT_SCOPE)