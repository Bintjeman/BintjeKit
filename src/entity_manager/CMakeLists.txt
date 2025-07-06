cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
target_sources(bintjekit PRIVATE
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}/include
        FILES
        ${PROJECT_SOURCE_DIR}/include/bintjekit/entity/entitymanager.hpp
        ${PROJECT_SOURCE_DIR}/include/bintjekit/entity/entitymanager.inl
        ${PROJECT_SOURCE_DIR}/include/bintjekit/entity/customgroup.hpp
        ${PROJECT_SOURCE_DIR}/include/bintjekit/entity/customgroup.inl
        PRIVATE
        #        entitymanager.cpp
        #        customgroup.cpp
        collection.cpp
        ientity.cpp

)
################################################################################