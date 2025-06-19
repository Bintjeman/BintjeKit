cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
add_executable(time_test time_test.cpp)
target_link_libraries(time_test
        PRIVATE
        time
        Catch2::Catch2WithMain
)

include(Catch)
catch_discover_tests(time_test)
