################################################################################
# CMakeLists.txt
# crée le 15.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
set(LIB_NAME sfml-imgui)
add_library(${LIB_NAME} STATIC)
set(SFML_IMGUI_MODULES)
set(SFML_IMGUI_SOURCES
        imgui_widgets.cpp
        imgui_draw.cpp
        imgui_demo.cpp
        imgui_tables.cpp
        imgui-SFML.cpp
        imgui.cpp
)
set(SFML_IMGUI_HEADERS
        imconfig.h
        imconfig-SFML.h
        imgui.h
        imgui-SFML.h
        imgui-SFML_export.h
        imgui_internal.h
        imstb_rectpack.h
        imstb_textedit.h
        imstb_truetype.h
)

target_sources(${LIB_NAME}
        PRIVATE
        ${SFML_IMGUI_SOURCES}
        PUBLIC
        FILE_SET CXX_MODULES
        BASE_DIRS
        FILES ${SFML_IMGUI_MODULES}
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
        FILES ${SFML_IMGUI_HEADERS}
)

target_include_directories(${LIB_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(${LIB_NAME} PRIVATE logger)
target_link_libraries(${LIB_NAME} PRIVATE SFML::Graphics)