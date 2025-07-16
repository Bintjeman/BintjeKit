cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
target_sources(bintjekit PRIVATE
        core.cpp
        core_builder.cpp
        module_set.cpp
        i_module.cpp
)