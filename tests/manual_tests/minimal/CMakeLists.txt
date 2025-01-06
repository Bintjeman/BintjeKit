################################################################################
# CMakeLists.txt
# crée le 05.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
add_executable(minimal_test)
set(SPDLOG_BUILD_SHARED=OFF)
set(CMAKE_PREFIX_PATH "$ENV{HOME}/.local/bnj_install" ${CMAKE_PREFIX_PATH})
find_package(spdlog CONFIG REQUIRED)

set(SOURCES
        main.cpp
)
set(MODULES
)
target_sources(minimal_test
        PRIVATE
        ${SOURCES}
        PUBLIC
        FILE_SET factory_modules TYPE CXX_MODULES FILES ${MODULES}
)


target_link_libraries(minimal_test PRIVATE
        bintjeKit
        spdlog::spdlog
)