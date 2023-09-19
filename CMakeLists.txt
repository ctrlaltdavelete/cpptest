cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(cppTest VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(UtilitiesLibrary)
add_subdirectory(HumanLibrary)
