################################################################################
# CMakeLists.txt
# crée le 15.01.25
# par bintjeman
################################################################################
message(STATUS "CMake script loaded depuis : ${CMAKE_CURRENT_LIST_FILE}")
list(APPEND BIK_HEADERS)
list(APPEND BIK_MODULES
        ${CMAKE_CURRENT_LIST_DIR}/common.cppm
        ${CMAKE_CURRENT_LIST_DIR}/core_info_provider.cppm
        ${CMAKE_CURRENT_LIST_DIR}/iactionreceiver.cppm
)
list(APPEND BIK_SOURCES)
set(BIK_HEADER ${BIK_HEADERS} PARENT_SCOPE)
set(BIK_MODULES ${BIK_MODULES} PARENT_SCOPE)
set(BIK_SOURCES ${BIK_SOURCES} PARENT_SCOPE)