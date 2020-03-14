cmake_minimum_required(VERSION 3.2)
project(ZenMockExamples)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${ZenUnitIncludeDirectory})
include_directories(${ZenMockIncludeDirectory})

file(GLOB_RECURSE sourceFilePaths *.h *.cpp)
source_group("" FILES ${sourceFilePaths})

add_executable(ZenMockExamples ${sourceFilePaths})

if(UNIX)
   target_link_libraries(ZenMockExamples stdc++fs)
endif()

EnablePrecompiledHeaders()
IfMSVCAddRunTestsPostBuildStep()

if(UNIX)
   if(CodeCovMode)
     target_link_libraries(ZenMockExamples CodeCovLibraryInterface)
   endif()
endif()
