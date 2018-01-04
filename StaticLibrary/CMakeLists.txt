cmake_minimum_required(VERSION 3.2)
project(StaticLibrary)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)
include_directories(${CMAKE_SOURCE_DIR})

file(GLOB_RECURSE Sources *.h *.cpp)
source_group("" FILES ${Sources})

replace(CMAKE_CXX_FLAGS "/Wall" "/W4")
add_library(StaticLibrary ${Sources})

EnablePrecompiledHeaders()
