cmake_minimum_required(VERSION 3.20)
project(MetalMockExamples)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${ZenUnitIncludeDirectory})

file(GLOB_RECURSE sourceFilePaths *.h *.cpp)
source_group("" FILES ${sourceFilePaths})

add_executable(MetalMockExamples ${sourceFilePaths})
if(UNIX AND NOT APPLE)
   target_link_libraries(MetalMockExamples stdc++fs)
endif()

if(UNIX)
   target_precompile_headers(MetalMockExamples PRIVATE pch.h)
elseif(MSVC)
   IfMSVCEnablePrecompiledHeaders()
   IfMSVCAddPostBuildStepToRunTests()
endif()

if(UNIX AND NOT APPLE)
   if(LCovCodeCoverageMode)
     target_link_libraries(MetalMockExamples CodeCovLibraryInterface)
   endif()
endif()
