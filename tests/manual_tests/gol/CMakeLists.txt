################################################################################
# CMakeLists.txt
# crée le 08.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
add_executable(gol_test)

set(SOURCES
        main.cpp
)

set(MODULES
        gol.cppm
        map.cppm
        gol_renderer.cppm
        renderer.cppm
        user_interface.cppm
        factory.cppm
)

target_sources(gol_test PRIVATE
        ${SOURCES}
        PUBLIC
        FILE_SET gol_module TYPE CXX_MODULES FILES ${MODULES}
)

target_link_libraries(gol_test PRIVATE bintjeKit)