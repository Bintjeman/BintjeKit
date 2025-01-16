################################################################################
# CMakeLists.txt
# crée le 15.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
set(LIB_NAME time)
add_library(${LIB_NAME} STATIC)
set(TIME_MODULES
        time.cppm
        pulser.cppm
        pulser_impl.cppm
        clock.cppm
        clock_impl.cppm
        utils.cppm
)
set(TIME_SOURCES)
set(TIME_HEADERS
        using.hpp
)

target_sources(${LIB_NAME}
        PRIVATE
        ${TIME_SOURCES}
        PUBLIC
        FILE_SET CXX_MODULES
        BASE_DIRS
        FILES ${TIME_MODULES}
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
        FILES ${TIME_HEADERS}
)

target_compile_features(${LIB_NAME} PRIVATE cxx_std_20)

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