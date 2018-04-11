cmake_minimum_required(VERSION 3.2)
project(ExampleTests)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${ZenMockIncludeDirectory})

file(GLOB Sources *.h *.cpp)
source_group("" FILES ${Sources})

add_executable(ExampleTests ${Sources})

EnablePrecompiledHeaders()
IfMSVCAddRunTestsPostBuildStep()

if(MSVC)
   replace(CMAKE_CXX_FLAGS "/Wall" "/W4")
endif()
