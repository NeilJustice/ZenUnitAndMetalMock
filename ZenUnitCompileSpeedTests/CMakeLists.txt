cmake_minimum_required(VERSION 3.2)
project(ZenUnitCompileSpeedTests)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${ZenUnitIncludeDirectory})

file(GLOB_RECURSE sourceFilePaths *.h *.cpp)
source_group("" FILES ${sourceFilePaths})

add_executable(ZenUnitCompileSpeedTests ${sourceFilePaths})

target_link_libraries(ZenUnitCompileSpeedTests)
if(UNIX AND NOT APPLE)
   target_link_libraries(ZenUnitCompileSpeedTests stdc++fs)
endif()

IfMSVCEnablePrecompiledHeaders()

if(UNIX AND NOT APPLE)
   if(LCovCodeCoverageMode)
     target_link_libraries(ZenUnitCompileSpeedTests CodeCovLibraryInterface)
   endif()
endif()
