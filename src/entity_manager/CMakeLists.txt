cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
target_sources(bintjekit
        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS ${PROJECT_SOURCE_DIR}/include
            FILES
        ${PROJECT_SOURCE_DIR}/include/bintjekit/entity/entity_manager.hpp
        ${PROJECT_SOURCE_DIR}/include/bintjekit/entity/entity_manager.inl
        ${PROJECT_SOURCE_DIR}/include/bintjekit/entity/custom_group.hpp
        ${PROJECT_SOURCE_DIR}/include/bintjekit/entity/custom_group.inl
)
target_sources(bintjekit PRIVATE
        collection.cpp
        ientity.cpp
)
################################################################################