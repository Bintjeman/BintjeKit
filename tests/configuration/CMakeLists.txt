cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
add_executable(configuration_test configuration_test.cpp)
target_link_libraries(configuration_test
        PRIVATE
        bintjekit
        Catch2::Catch2WithMain
)
include(Catch)
catch_discover_tests(configuration_test)
