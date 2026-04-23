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

set(CMAKE_VS_WINRT_BY_DEFAULT 1)

project(winapi-understanding DESCRIPTION "Understanding Win32 API features" VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

find_package(wil CONFIG REQUIRED)
find_package(cppwinrt CONFIG REQUIRED)

add_library(pch STATIC src/dummy_pch.cpp)
target_precompile_headers(pch PUBLIC src/pch.hpp)
target_link_libraries(pch PUBLIC WIL::WIL)

add_executable(overlapped src/overlapped.cpp)
target_precompile_headers(overlapped REUSE_FROM pch)

add_executable(create_file src/create_file.cpp)
target_precompile_headers(create_file REUSE_FROM pch)

add_executable(process_spawner src/process_spawner.cpp)
target_precompile_headers(process_spawner REUSE_FROM pch)

add_executable(register_modifier src/register_modifier.cpp)
target_precompile_headers(register_modifier REUSE_FROM pch)
target_link_libraries(register_modifier PRIVATE pch iphlpapi pdh wbemuuid ws2_32 shlwapi netapi32 fltlib rpcrt4)

add_executable(screen_capture src/screen_capture.cpp)
target_precompile_headers(screen_capture REUSE_FROM pch)
target_link_libraries(screen_capture PRIVATE pch Microsoft::CppWinRT windowsapp)

add_executable(parent_process_detector src/parent_process_detector.cpp)
target_precompile_headers(parent_process_detector REUSE_FROM pch)
target_link_libraries(parent_process_detector PRIVATE pch)

add_executable(message_box src/message_box.cpp)
target_precompile_headers(message_box REUSE_FROM pch)
target_link_libraries(message_box PRIVATE pch)