cmake_minimum_required(VERSION 3.20)
project(ZenUnitCompileSpeedTests)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${ZenUnitIncludeDirectory})

file(GLOB_RECURSE sourceFilePaths *.h *.cpp)
source_group("" FILES ${sourceFilePaths})

add_executable(ZenUnitCompileSpeedTests ${sourceFilePaths})

target_link_libraries(ZenUnitCompileSpeedTests)

if(UNIX)
   target_precompile_headers(ZenUnitCompileSpeedTests PRIVATE pch.h)
elseif(MSVC)
   IfMSVCEnablePrecompiledHeaders()
endif()

if(UNIX AND NOT APPLE)
   if(LCovCodeCoverageMode)
     target_link_libraries(ZenUnitCompileSpeedTests CodeCovLibraryInterface)
   endif()
endif()
