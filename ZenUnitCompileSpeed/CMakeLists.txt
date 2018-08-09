cmake_minimum_required(VERSION 3.2)
project(ZenUnitCompileSpeed)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/ZenUnit)

source_group("" FILES ZenUnitCompileSpeedMain.cpp pch.h pch.cpp)
file(GLOB_RECURSE Sources *.h *.cpp)

add_executable(ZenUnitCompileSpeed ${Sources})
target_link_libraries(ZenUnitCompileSpeed)

if(MSVC)
   replace(CMAKE_CXX_FLAGS "/Wall" "/W4")
endif()
