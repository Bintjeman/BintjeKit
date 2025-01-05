################################################################################
# 
# crée le 05.01.25
# par bintjeman
################################################################################
cmake_minimum_required(VERSION 3.30)
project(BintjeKit LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

add_library(BintjeKit STATIC library.cpp)
