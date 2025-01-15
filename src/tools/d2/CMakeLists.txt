################################################################################
# CMakeLists.txt
# crée le 15.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
set(LIB_NAME d2)
add_library(${LIB_NAME} STATIC)
set(D2_MODULES
        d2.cppm
)
set(D2_SOURCES)
set(D2_HEADERS
)

target_sources(${LIB_NAME}
        PRIVATE
        ${D2_SOURCES}
        PUBLIC
        FILE_SET CXX_MODULES
        BASE_DIRS
        FILES ${D2_MODULES}
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
        FILES ${D2_HEADERS}
)

target_link_libraries(${LIB_NAME} PRIVATE SFML::System)


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