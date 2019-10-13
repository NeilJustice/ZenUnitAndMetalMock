cmake_minimum_required(VERSION 3.2)
project(ZenUnitExamples)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

include_directories(${ZenUnitIncludeDirectory})
include_directories(${ZenMockIncludeDirectory})

file(GLOB_RECURSE Sources *.h *.cpp)

add_executable(ZenUnitExamples ${Sources})
if(UNIX)
   target_link_libraries(ZenUnitExamples stdc++fs)
endif()

EnablePrecompiledHeaders()
IfMSVCAddRunTestsPostBuildStep()
