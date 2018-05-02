cmake_minimum_required(VERSION 3.2)
project(ZenUnitExamples)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/ZenUnit)
include_directories(${ZenMockIncludeDirectory})

file(GLOB Sources *.h *.cpp)
source_group("" FILES ${Sources})

add_executable(ZenUnitExamples ${Sources})

EnablePrecompiledHeaders()
IfMSVCAddRunTestsPostBuildStep()

if(MSVC)
   replace(CMAKE_CXX_FLAGS "/Wall" "/W4")
endif()
