################################################################################
# CMakeLists.txt
# crée le 08.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
set(MODULES
        renderer.cppm
        renderer_interface.cppm
        renderer_iml.cppm
)
target_sources(bintjeKit PRIVATE
        PUBLIC
        FILE_SET renderer_modules TYPE CXX_MODULES FILES ${MODULES}
)