cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
add_executable(user_classes
        src/main.cpp
        src/event_manager.cpp
        src/main_window.cpp

)
target_include_directories(user_classes PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include

)
target_link_libraries(user_classes PUBLIC
        BintjeKit::BintjeKit
#        BintjeKit::EventManager
#        BintjeKit::Core
#        BintjeKit::Window
        SFML::Window
        SFML::System
        SFML::Graphics
)