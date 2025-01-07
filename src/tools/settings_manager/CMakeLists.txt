################################################################################
# CMakeLists.txt
# crée le 05.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
set(MODULES
        settings.cppm
        settings_interface.cppm
        settings_impl.cppm
        node.cppm
        node_impl.cppm
        settings_nlohmann_extension.cppm
)
target_sources(bintjeKit
        PUBLIC
        FILE_SET settings_modules TYPE CXX_MODULES FILES ${MODULES}  # Interface principale
)