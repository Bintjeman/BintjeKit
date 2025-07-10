cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
target_sources(bintjekit
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}/include
        FILES
        ${CMAKE_SOURCE_DIR}/include/bintjekit/entity/entity_manager.hpp
        ${CMAKE_SOURCE_DIR}/include/bintjekit/entity/entity_manager.inl
        ${CMAKE_SOURCE_DIR}/include/bintjekit/entity/entity_collection.hpp
        ${CMAKE_SOURCE_DIR}/include/bintjekit/entity/typed_collection.hpp
        ${CMAKE_SOURCE_DIR}/include/bintjekit/entity/typed_collection.inl
        ${CMAKE_SOURCE_DIR}/include/bintjekit/entity/components/component_register.inl
        ${CMAKE_SOURCE_DIR}/include/bintjekit/entity/components/component.hpp
        ${CMAKE_SOURCE_DIR}/include/bintjekit/entity/components/component_register.hpp
)
target_sources(bintjekit PRIVATE
        ientity.cpp
        entity_collection.cpp
        entity_manager.cpp
        typed_collection.cpp
        components/component.cpp
        components/component_register.cpp
)
################################################################################