cmake_minimum_required(VERSION 3.31)
include_guard(GLOBAL)
message("Actual *.cmake: ${CMAKE_CURRENT_LIST_FILE}")
################################################################################
set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/third_party" CACHE PATH "Downloaded dependencies location")
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
set(FETCHCONTENT_QUIET OFF)
if(NOT EXISTS "${FETCHCONTENT_BASE_DIR}")
    file(MAKE_DIRECTORY "${FETCHCONTENT_BASE_DIR}")
endif()
# Pour chaque dépendance, ajoutez une vérification
if(NOT EXISTS "${FETCHCONTENT_BASE_DIR}/sfml-src")
    set(NEED_SFML TRUE)
endif()
if(NOT EXISTS "${FETCHCONTENT_BASE_DIR}/spdlog-src")
    set(NEED_SPDLOG TRUE)
endif()
if(NOT EXISTS "${FETCHCONTENT_BASE_DIR}/imgui-src")
    set(NEED_IMGUI TRUE)
endif()
if(NOT EXISTS "${FETCHCONTENT_BASE_DIR}/imgui-sfml-src")
    set(NEED_IMGUI-SFML TRUE)
endif()
if(NOT EXISTS "${FETCHCONTENT_BASE_DIR}/json-src")
    set(NEED_JSON TRUE)
endif()
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
set(SPDLOG_FMT_EXTERNAL OFF)
set(SPDLOG_COMPILED_LIB ON)
FetchContent_Declare(spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.13.0
        GIT_SHALLOW ON
        SYSTEM
)
################################################################################
# Ajout de ImGui
FetchContent_Declare(imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.91.1
        GIT_SHALLOW ON
        SYSTEM
)
################################################################################
FetchContent_MakeAvailable(SFML spdlog imgui)
# Ajoutez ces lignes pour configurer fmt intégré à spdlog
if(TARGET spdlog::spdlog)
    get_target_property(fmt_target spdlog::spdlog INTERFACE_LINK_LIBRARIES)
    if(TARGET fmt::fmt)
        set_target_properties(fmt::fmt PROPERTIES
                INTERFACE_SYSTEM_INCLUDE_DIRECTORIES $<TARGET_PROPERTY:fmt::fmt,INTERFACE_INCLUDE_DIRECTORIES>
        )
        configure_external_library_options(fmt::fmt)
    endif()
endif()
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
