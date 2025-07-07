cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
target_sources(bintjekit
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}/include
        FILES
        ${CMAKE_SOURCE_DIR}/include/bintjekit/entity/entity_collection.hpp
        ${CMAKE_SOURCE_DIR}/include/bintjekit/entity/entity_collection.inl
        ${CMAKE_SOURCE_DIR}/include/bintjekit/entity/entity_manager.hpp
)
target_sources(bintjekit PRIVATE
        ientity.cpp
)
################################################################################