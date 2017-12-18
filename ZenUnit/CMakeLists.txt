cmake_minimum_required(VERSION 3.2)
project(ZenUnit)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_SOURCE_DIR})

file(GLOB TopLevelFiles *.h *.cpp)
source_group("" FILES ${TopLevelFiles})
file(GLOB_RECURSE Sources *.h *.cpp)

add_library(ZenUnit ${Sources})

install(DIRECTORY .
        DESTINATION include/ZenUnit/ZenUnit
        FILES_MATCHING REGEX "ZenUnit.h|ZenMock.h"
        PATTERN REGEX "CMakeFiles|Release|RelWithDebInfo|MinSizeRel|ZenUnit.dir" EXCLUDE)
