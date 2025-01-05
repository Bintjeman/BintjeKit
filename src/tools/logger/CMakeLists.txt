################################################################################
# CMakeLists.txt
# crée le 05.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
set(MODULES
        logger.cppm
        logger_interface.cppm
        logger_impl.cppm
)
target_sources(bintjeKit
        PUBLIC
        FILE_SET logger_modules TYPE CXX_MODULES FILES ${MODULES}  # Interface principale
)