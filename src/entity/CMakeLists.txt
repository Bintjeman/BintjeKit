cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
target_sources(bintjekit
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}/include
        FILES
        ${CMAKE_SOURCE_DIR}/include/bintjekit/entity/entity_manager.inl
        ${CMAKE_SOURCE_DIR}/include/bintjekit/entity/entity_manager.hpp
        ${CMAKE_SOURCE_DIR}/include/bintjekit/entity/combined_typed_collection.hpp
        ${CMAKE_SOURCE_DIR}/include/bintjekit/entity/combined_typed_collection.inl
        ${CMAKE_SOURCE_DIR}/include/bintjekit/entity/typed_collection.inl
        ${CMAKE_SOURCE_DIR}/include/bintjekit/entity/typed_collection.hpp
        ${CMAKE_SOURCE_DIR}/include/bintjekit/entity/entity_collection.hpp
        ${CMAKE_SOURCE_DIR}/include/bintjekit/entity/components/component_view.inl
        ${CMAKE_SOURCE_DIR}/include/bintjekit/entity/components/component_view.hpp
        ${CMAKE_SOURCE_DIR}/include/bintjekit/entity/components/component_register.inl
        ${CMAKE_SOURCE_DIR}/include/bintjekit/entity/components/component_register.hpp
        ${CMAKE_SOURCE_DIR}/include/bintjekit/entity/components/component.hpp
)
target_sources(bintjekit PRIVATE
        entity_manager.cpp
        typed_collection.cpp
        entity_collection.cpp
        components/component_view.cpp
        components/component_register.cpp
        components/component.cpp
        ientity.cpp
)
################################################################################