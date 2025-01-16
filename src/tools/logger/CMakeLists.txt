################################################################################
# CMakeLists.txt
# crée le 15.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
set(LIB_NAME logger)
add_library(${LIB_NAME} STATIC)
set(CMAKE_CXX_MODULE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/pcm")
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

target_compile_features(${LIB_NAME} PRIVATE cxx_std_20)

target_link_libraries(${LIB_NAME} PRIVATE SFML::Graphics)

target_include_directories(${LIB_NAME} PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)

# Installer la bibliothèque et ses file sets
install(TARGETS ${LIB_NAME}
        EXPORT bintjeKitTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
        FILE_SET HEADERS DESTINATION include/bintjeKit
        FILE_SET CXX_MODULES DESTINATION lib/modules/bintjeKit/logger
)