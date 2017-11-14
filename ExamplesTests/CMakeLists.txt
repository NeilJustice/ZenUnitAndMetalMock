cmake_minimum_required(VERSION 3.2)
project(ExamplesTests)
include(${CMAKE_SOURCE_DIR}/ZenUnitHelloWorld/CMakeMacros.cmake)

include_directories(${CMAKE_SOURCE_DIR})
file(GLOB Sources *.h *.cpp)
source_group("" FILES ${Sources})

add_executable(ExamplesTests ${Sources})
target_link_libraries(ExamplesTests Examples)

EnablePrecompiledHeaders()
IfMSVCAddRunTestsPostBuildStep()

if(MSVC)
   replace(CMAKE_CXX_FLAGS "/Wall" "/W4")
endif()

