################################################################################
# CMakeLists.txt
# crée le 07.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
add_executable(window_component_test)
set(SPDLOG_BUILD_SHARED=OFF)
set(CMAKE_PREFIX_PATH "$ENV{HOME}/.local/bnj_install" ${CMAKE_PREFIX_PATH})
find_package(spdlog CONFIG REQUIRED)

set(SOURCES
        main.cpp
        window.cpp
)
set(MODULES
        window.cppm
)
target_sources(window_component_test
        PRIVATE
        ${SOURCES}
        PUBLIC
        FILE_SET factory_modules TYPE CXX_MODULES FILES ${MODULES}
)