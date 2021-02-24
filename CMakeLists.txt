cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(code)

enable_language(C)
enable_language(CXX)
enable_language(ASM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
find_package(SDL2 REQUIRED)

add_subdirectory(code)
