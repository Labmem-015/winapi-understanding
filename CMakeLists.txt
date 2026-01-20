cmake_minimum_required(VERSION 3.31 FATAL_ERROR)
cmake_policy(VERSION 3.31)

# Those options may be set in the preset file
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 23)

project(winapi-understanding DESCRIPTION "Understanding Win32 API features" VERSION 0.1.0 LANGUAGES CXX)

add_library(pch STATIC src/dummy_pch.cpp)
target_precompile_headers(pch PUBLIC src/pch.hpp)

add_executable(overlapped src/overlapped.cpp)
target_precompile_headers(overlapped REUSE_FROM pch)
