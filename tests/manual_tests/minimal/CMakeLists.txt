################################################################################
# CMakeLists.txt
# crée le 05.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
add_executable(minimal_test)
target_sources(minimal_test PRIVATE main.cpp)
target_link_libraries(minimal_test PRIVATE bintjeKit)