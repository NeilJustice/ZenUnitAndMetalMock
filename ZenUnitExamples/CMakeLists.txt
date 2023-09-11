cmake_minimum_required(VERSION 3.20)
project(ZenUnitExamples)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${ZenUnitIncludeDirectory})

source_group("" FILES
   ZenUnitExamplesTestsMain.cpp
   pch.h
   pch.cpp
   EveryZenUnitAssertion.cpp
   FizzBuzzTests.cpp
   SetTests.cpp
   STARTUPAndCLEANUPTests.cpp
   TypeParameterizedTestClass.cpp
   ZenUnitExamplesTestsMain.cpp)
file(GLOB_RECURSE sourceFilePaths *.h *.cpp)

add_executable(ZenUnitExamples ${sourceFilePaths})
if(UNIX AND NOT APPLE)
   target_link_libraries(ZenUnitExamples stdc++fs)
endif()

IfMSVCEnablePrecompiledHeaders()
IfMSVCAddPostBuildStepToRunTests()

if(UNIX AND NOT APPLE)
   if(LCovCodeCoverageMode)
     target_link_libraries(ZenUnitExamples CodeCovLibraryInterface)
   endif()
endif()
