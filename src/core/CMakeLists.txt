################################################################################
# CMakeLists.txt
# crée le 05.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
set(MODULES
        core.cppm
        core_interface.cppm
        core_impl.cppm
)
target_sources(bintjeKit
        PUBLIC
        FILE_SET window_modules TYPE CXX_MODULES FILES ${MODULES}  # Interface principale
)