cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
add_library(time OBJECT
        src/time/time.cpp
)
target_include_directories(time
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/common/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

)

target_link_libraries(time PRIVATE SFML::System)

# Installation des headers de time
install(
        DIRECTORY ${PROJECT_SOURCE_DIR}/common/include/time
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
