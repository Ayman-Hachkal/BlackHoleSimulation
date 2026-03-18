cmake_minimum_required(VERSION 3.10)

set(VCPKG_TARGET_TRIPLET x64-osx-dynamic) # Force vcpkg to use dynamic libs
project(BlackHoleSimulation LANGUAGES CXX)

find_package(raylib CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

add_executable(BlackHoleSimulation main.cpp)

target_link_libraries(BlackHoleSimulation raylib)
