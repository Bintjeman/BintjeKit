################################################################################
# CMakeLists.txt
# crée le 07.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
set(MODULES
        ui.cppm
        ui_interface.cppm
        ui_impl.cppm
)
target_sources(bintjeKit
        PUBLIC
        FILE_SET ui_modules TYPE CXX_MODULES FILES ${MODULES}  # Interface principale
)