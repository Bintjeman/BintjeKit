cmake_minimum_required(VERSION 3.31)
message("Actual CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}")
################################################################################
target_sources(time
        PRIVATE
        src/time/time.cpp
)
target_include_directories(time
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/common/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

)
target_compile_features(time PUBLIC cxx_std_20)
target_link_libraries(time PUBLIC SFML::System)
# Installation des headers de time
install(
        DIRECTORY include/bintjekit/utils/time
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/bintjekit/utils
        FILES_MATCHING PATTERN "*.hpp" PATTERN "*.inl"
)
################################################################################
target_sources(random
        PRIVATE
        src/random/random_engine.cpp
)
target_include_directories(random
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/common/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_features(random PUBLIC cxx_std_20)
#target_link_libraries(time PUBLIC SFML::System)
# Installation des headers de time
install(
        DIRECTORY include/bintjekit/utils/random
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/bintjekit/utils
        FILES_MATCHING PATTERN "*.hpp" PATTERN "*.inl"
)
################################################################################
target_sources(d2
        PRIVATE
        src/d2/d2.cpp
)
target_include_directories(d2
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/common/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_features(d2 PUBLIC cxx_std_20)
#target_link_libraries(time PUBLIC SFML::System)
# Installation des headers de time
install(
        DIRECTORY include/bintjekit/utils/d2
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/bintjekit/utils
        FILES_MATCHING PATTERN "*.hpp" PATTERN "*.inl"
)