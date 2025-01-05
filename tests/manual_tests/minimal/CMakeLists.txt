################################################################################
# CMakeLists.txt
# crée le 05.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
add_executable(minimal_test)

set(SOURCES
        main.cpp
        factory_child.cpp
        window_child.cpp
)
set(MODULES
        factory_child.cppm
        window_child.cppm
)
target_sources(minimal_test
        PRIVATE
        ${SOURCES}
        PUBLIC
        FILE_SET factory_modules TYPE CXX_MODULES FILES ${MODULES}
)


target_link_libraries(minimal_test PRIVATE bintjeKit)