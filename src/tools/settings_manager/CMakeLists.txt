################################################################################
# CMakeLists.txt
# crée le 15.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
set(LIB_NAME settings)
add_library(${LIB_NAME} STATIC)
set(SETTINGS_MODULES
        settings.cppm
        settings_interface.cppm
        settings_impl.cppm
        node.cppm
        node_impl.cppm
        settings_nlohmann_extension.cppm
)
set(SETTINGS_SOURCES)
set(SETTINGS_HEADERS)

target_sources(${LIB_NAME}
        PRIVATE
        ${SETTINGS_SOURCES}
        PUBLIC
        FILE_SET CXX_MODULES
        BASE_DIRS
        FILES ${SETTINGS_MODULES}
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
        FILES ${SETTINGS_HEADERS}
)

target_include_directories(${LIB_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(${LIB_NAME} PRIVATE logger)
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
        FILE_SET CXX_MODULES DESTINATION lib/modules
)