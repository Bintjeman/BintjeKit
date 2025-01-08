################################################################################
# CMakeLists.txt
# crée le 08.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
set(MODULES
        common.cppm
        iactionreceiver.cppm

)
target_sources(bintjeKit
        PUBLIC
        FILE_SET action_modules TYPE CXX_MODULES FILES ${MODULES}  # Interface principale
)