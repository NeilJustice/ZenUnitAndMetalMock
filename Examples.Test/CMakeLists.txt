cmake_minimum_required(VERSION 3.5)
project(Examples.Test)
include(${CMAKE_SOURCE_DIR}/ZenUnitHelloWorld/CMakeMacros.cmake)

include_directories(${CMAKE_SOURCE_DIR})
file(GLOB Sources *.h *.cpp)
source_group("" FILES ${Sources})

add_executable(Examples.Test ${Sources})
target_link_libraries(Examples.Test ZenUnit Examples)

EnablePrecompiledHeaders()
IfMSVCAddRunTestsPostBuildStep()

if(MSVC)
   replace(CMAKE_CXX_FLAGS "/Wall" "/W4")
endif()
