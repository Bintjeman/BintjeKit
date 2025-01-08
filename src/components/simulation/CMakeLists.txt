################################################################################
# CMakeLists.txt
# crée le 08.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
set(MODULES
        simulation.cppm
        simulation_interface.cppm
        simulation_impl.cppm
)
target_sources(bintjeKit PRIVATE
        PUBLIC
        FILE_SET simulation_modules TYPE CXX_MODULES FILES ${MODULES}
)