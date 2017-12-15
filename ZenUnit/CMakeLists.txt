cmake_minimum_required(VERSION 3.2)
project(ZenUnit)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_SOURCE_DIR})

folder_source_group(ZenMock)
folder_source_group_subfolder(ZenMock 0)
folder_source_group_subfolder(ZenMock 1)
folder_source_group_subfolder(ZenMock 2)
folder_source_group_subfolder(ZenMock 3)
folder_source_group_subfolder(ZenMock 4)
folder_source_group_subfolder(ZenMock 5)
folder_source_group_subfolder(ZenMock 6)
folder_source_group_subfolder(ZenMock 7)
folder_source_group_subfolder(ZenMock 8)
folder_source_group_subfolder(ZenMock 9)
folder_source_group_subfolder(ZenMock 10)
folder_source_group_subfolder(ZenMock Exceptions)

file(GLOB TopLevelFiles *.h *.cpp)
source_group("" FILES ${TopLevelFiles})
file(GLOB_RECURSE Sources *.h *.cpp)

add_library(ZenUnit ${Sources})

install(DIRECTORY .
        CONFIGURATIONS Debug
        DESTINATION include/ZenUnit/ZenUnit
        FILES_MATCHING REGEX "\\.h$|\\.cpp$"
        PATTERN REGEX "CMakeFiles|Release|RelWithDebInfo|MinSizeRel|ZenUnit.dir" EXCLUDE)
