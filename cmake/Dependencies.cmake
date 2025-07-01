cmake_minimum_required(VERSION 3.31)
include_guard(GLOBAL)
message("Actual *.cmake: ${CMAKE_CURRENT_LIST_FILE}")
################################################################################
include(FetchContent)
include(cmake/CompilerOption.cmake)
################################################################################
# Configuration de SFML
set(SFML_BUILD_AUDIO FALSE)
set(SFML_BUILD_NETWORK FALSE)
set(SFML_BUILD_EXAMPLES FALSE)
set(SFML_BUILD_DOC FALSE)
set(SFML_INSTALL_PKGCONFIG_FILES FALSE)
set(SFML_BUILD_FRAMEWORKS FALSE)
set(SFML_INSTALL_XCODE_TEMPLATES FALSE)
set(BUILD_SHARED_LIBS FALSE)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        #        EXCLUDE_FROM_ALL
        SYSTEM
)
################################################################################
#FetchContent_Declare(
#        fmt
#        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
#        GIT_TAG 11.2.1
#)
#FetchContent_MakeAvailable(fmt)
################################################################################
set(SPDLOG_FMT_EXTERNAL OFF)
set(SPDLOG_COMPILED_LIB ON)
set(SPDLOG_USE_STD_FORMAT OFF)
#set(SPDLOG_FMT_EXTERNAL_HO ON)
#set(SPDLOG_ENABLE_PCH OFF)  # Désactive le precompiled header qui peut causer des problèmes
FetchContent_Declare(spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.15.3
        GIT_SHALLOW ON
        SYSTEM
)
FetchContent_MakeAvailable( spdlog)
################################################################################
# Ajout de ImGui
FetchContent_Declare(imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.91.1
        GIT_SHALLOW ON
        SYSTEM
)
################################################################################
FetchContent_MakeAvailable(SFML imgui)
configure_target_options(imgui EXTERNAL)
configure_target_options(SFML EXTERNAL)
configure_target_options(spdlog EXTERNAL)
get_target_property(SPDLOG_INCLUDES spdlog INTERFACE_INCLUDE_DIRECTORIES)
################################################################################
# Ajout de SFML-ImGui
FetchContent_Declare(imgui-sfml
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
        GIT_TAG v3.0
        GIT_SHALLOW ON
        SYSTEM
)
################################################################################
# Configuration pour ImGui-SFML
set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)
FetchContent_MakeAvailable(imgui-sfml)
################################################################################
# Ajout de nlohmann_json
set(JSON_Install ON)
set(JSON_BuildTests OFF)
set(JSON_MultipleHeaders OFF)
FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
        GIT_SHALLOW ON
        SYSTEM
)
FetchContent_MakeAvailable(json)
################################################################################
