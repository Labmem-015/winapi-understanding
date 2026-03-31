cmake_minimum_required(VERSION 3.31 FATAL_ERROR)
cmake_policy(VERSION 3.31)

if(NOT DEFINED ENV{VCPKG_ROOT})
	message(FATAL_ERROR "VCPKG_ROOT is not defined!")
else()
	message("VCPKG_ROOT is defined as $ENV{VCPKG_ROOT}")
endif()

# Those options may be set in the preset file
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 23)

project(winapi-understanding DESCRIPTION "Understanding Win32 API features" VERSION 0.1.0 LANGUAGES CXX)

find_package(wil CONFIG REQUIRED)

add_library(pch STATIC src/dummy_pch.cpp)
target_precompile_headers(pch PUBLIC src/pch.hpp)

add_executable(overlapped src/overlapped.cpp)
target_precompile_headers(overlapped REUSE_FROM pch)

add_executable(create_file src/create_file.cpp)
target_precompile_headers(create_file REUSE_FROM pch)

add_executable(process_spawner src/process_spawner.cpp)
target_precompile_headers(process_spawner REUSE_FROM pch)

add_executable(register_modifier src/register_modifier.cpp)
target_precompile_headers(register_modifier REUSE_FROM pch)
target_link_libraries(register_modifier PUBLIC WIL::WIL iphlpapi pdh wbemuuid ws2_32 shlwapi netapi32 fltlib rpcrt4)
