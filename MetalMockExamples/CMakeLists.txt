cmake_minimum_required(VERSION 3.20)
project(MetalMockExamples)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${ZenUnitIncludeDirectory})

file(GLOB_RECURSE sourceFilePaths *.h *.cpp)
source_group("" FILES ${sourceFilePaths})

add_executable(MetalMockExamples ${sourceFilePaths})
set_property(TARGET MetalMockExamples PROPERTY CXX_STANDARD 20)
if(UNIX AND NOT APPLE)
   target_link_libraries(MetalMockExamples stdc++fs)
endif()

IfMSVCEnablePrecompiledHeaders()
IfMSVCAddPostBuildStepToRunTests()

if(UNIX AND NOT APPLE)
   if(LCovCodeCoverageMode)
     target_link_libraries(MetalMockExamples CodeCovLibraryInterface)
   endif()
endif()
