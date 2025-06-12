cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
add_library(bintjekit_engine OBJECT
        i_engine.cpp
        i_playground.cpp
)
target_include_directories(bintjekit_engine
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
set_target_properties(bintjekit_engine PROPERTIES
        VERSION ${PROJECT_VERSION}
        POSITION_INDEPENDENT_CODE ON
)
target_link_libraries(bintjekit_engine
        PUBLIC
)
add_library(bintjekit_engine_static STATIC
        $<TARGET_OBJECTS:bintjekit_engine>
)
target_link_libraries(bintjekit_engine_static
        PUBLIC
        bintjekit_engine
)
add_library(BintjeKit::Engine ALIAS bintjekit_engine_static)