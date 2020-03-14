cmake_minimum_required(VERSION 3.2)
project(ZenUnitTestUtils)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${ZenUnitIncludeDirectory})

folder_source_group(Equalizers)

file(GLOB_RECURSE sourceFilePaths *.h *.cpp)
source_group("" FILES ${sourceFilePaths})

add_library(ZenUnitTestUtils ${sourceFilePaths})

EnablePrecompiledHeaders()

if(UNIX)
   if(CodeCovMode)
     target_link_libraries(ZenUnitTestUtils CodeCovLibraryInterface)
   endif()
endif()
