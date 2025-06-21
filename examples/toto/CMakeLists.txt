cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
project(Toto)
################################################################################
 include(cmake/ConfigureCmake.cmake)
 include(cmake/Dependencies.cmake)
################################################################################
add_executable(toto)
################################################################################
add_subdirectory(src)
################################################################################
target_link_libraries(toto PRIVATE
        bintjekit
#        spdlog::spdlog
)
target_include_directories(toto PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        $ENV{HOME}/.local/include
)