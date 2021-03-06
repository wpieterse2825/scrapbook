cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(wpietersexyz_code)

enable_language(C)
enable_language(CXX)
enable_language(ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
find_package(SDL2 REQUIRED)
find_package(Vulkan REQUIRED)

add_subdirectory(randoms)
