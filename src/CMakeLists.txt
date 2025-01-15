################################################################################
# CMakeLists.txt
# crée le 05.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")

add_library(bintjeKit STATIC)
set_target_properties(bintjeKit PROPERTIES EXPORT_NAME bintjeKit)

set(BIK_HEADERS "")
set(BIK_MODULES "")
set(BIK_SOURCES "")

find_package(fmt CONFIG REQUIRED)
set(SPDLOG_BUILD_SHARED=OFF)
find_package(spdlog CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
set(SFML_STATIC_LIBRARIES ON)
find_package(SFML 3 COMPONENTS REQUIRED System Window Graphics)

add_subdirectory(external)
add_subdirectory(tools)

add_subdirectory(components)
add_subdirectory(factory)
add_subdirectory(core)

message("BIK_HEADERS: ${BIK_HEADERS}")
message("BIK_SOURCES: ${BIK_SOURCES}")
message("BIK_MODULES: ${BIK_MODULES}")

#set(IMGUI_SOURCES
#        external/dear_imgui/imgui-SFML.cpp
#        external/dear_imgui/imgui.cpp
#        external/dear_imgui/imgui_widgets.cpp
#        external/dear_imgui/imgui_draw.cpp
#        external/dear_imgui/imgui_tables.cpp
#        external/dear_imgui/imgui_demo.cpp
#)
#set(IMGUI_HEADERS
#        external/dear_imgui/imconfig.h
#        external/dear_imgui/imgui.h
#        external/dear_imgui/imgui_internal.h
#        external/dear_imgui/imstb_rectpack.h
#        external/dear_imgui/imstb_textedit.h
#        external/dear_imgui/imstb_truetype.h
#        external/dear_imgui/imgui-SFML.h
#        external/dear_imgui/imgui-SFML_export.h
#)
#
#set(BIK_SOURCES)
#
#set(BIK_MODULES
#        tools/d2/d2.cppm
#        tools/time/utils.cppm
#        tools/time/clock.cppm
#        tools/time/clock_impl.cppm
#        tools/time/pulser.cppm
#        tools/time/pulser_impl.cppm
#        tools/time/time.cppm
#        tools/settings_manager/node.cppm
#        tools/settings_manager/node_impl.cppm
#        tools/settings_manager/settings.cppm
#        tools/settings_manager/settings_impl.cppm
#        tools/settings_manager/settings_interface.cppm
#        tools/settings_manager/settings_nlohmann_extension.cppm
#        tools/logger/logger_extension.cppm
#        tools/logger/logger_impl.cppm
#        tools/logger/logger_interface.cppm
#        tools/logger/logger.cppm
#        factory/factory_interface.cppm
#        factory/factory_impl.cppm
#        factory/factory.cppm
#        core/core_interface.cppm
#        core/core_impl.cppm
#        core/core.cppm
#        components/window/window_interface.cppm
#        components/window/window_impl.cppm
#        components/window/window.cppm
#        components/ui/ui_interface.cppm
#        components/ui/ui_impl.cppm
#        components/ui/ui.cppm
#        components/renderer/renderer_interface.cppm
#        components/renderer/renderer_iml.cppm
#        components/renderer/renderer.cppm
#        components/playground/playground_interface.cppm
#        components/playground/playground_impl.cppm
#        components/playground/playground.cppm
#        components/imgui_wrapper/imgui_wrapper_interface.cppm
#        components/imgui_wrapper/imgui_wrapper_impl.cppm
#        components/imgui_wrapper/imgui_wrapper.cppm
#        components/common/core_info_provider.cppm
#        components/common/iactionreceiver.cppm
#        components/common/common.cppm
#)
set(BIK_HEADERS
        tools/logger/logger_define.hpp
        tools/time/using.hpp
)

target_include_directories(bintjeKit
        PUBLIC
        ${CMAKE_INSTALL_PREFIX}/include
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(bintjeKit
        PRIVATE
        ${BIK_SOURCES}
        ${IMGUI_SOURCES}
        PUBLIC
        FILE_SET CXX_MODULES
        BASE_DIRS
        FILES ${BIK_MODULES}        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
        FILES ${BIK_HEADERS} ${IMGUI_HEADERS}
)

target_compile_features(bintjeKit PRIVATE cxx_std_20)

target_link_libraries(bintjeKit
        PRIVATE sfml-imgui time settings d2
)
target_link_libraries(bintjeKit
        PRIVATE fmt::fmt spdlog::spdlog SFML::Window SFML::Graphics SFML::System nlohmann_json::nlohmann_json
)
