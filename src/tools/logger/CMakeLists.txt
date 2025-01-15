################################################################################
# CMakeLists.txt
# crée le 15.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
set(LIB_NAME logger)
add_library(${LIB_NAME} STATIC)
set(LOGGER_MODULES
        logger.cppm
        logger_interface.cppm
        logger_impl.cppm
        logger_extension.cppm
)
set(LOGGER_SOURCES)
set(LOGGER_HEADERS
        logger_define.hpp
)

target_sources(${LIB_NAME}
        PRIVATE
        ${LOGGER_SOURCES}
        PUBLIC
        FILE_SET CXX_MODULES
        BASE_DIRS
        FILES ${LOGGER_MODULES}
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
        FILES ${LOGGER_HEADERS}
)

target_link_libraries(${LIB_NAME} PRIVATE SFML::Graphics)