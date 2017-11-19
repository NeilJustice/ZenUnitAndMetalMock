cmake_minimum_required(VERSION 3.2)
project(StaticLibrary)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

replace(CMAKE_CXX_FLAGS "/Wall" "/W4")

file(GLOB_RECURSE Sources *.h *.cpp)
source_group("" FILES ${Sources})

add_library(StaticLibrary ${Sources})

EnablePrecompiledHeaders()
