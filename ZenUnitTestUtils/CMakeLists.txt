cmake_minimum_required(VERSION 3.2)
project(ZenUnitTestUtils)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${ZenUnitIncludeDirectory})

folder_source_group(Equalizers)

file(GLOB_RECURSE Sources *.h *.cpp)
source_group("" FILES ${Sources})

add_library(ZenUnitTestUtils ${Sources})

EnablePrecompiledHeaders()
