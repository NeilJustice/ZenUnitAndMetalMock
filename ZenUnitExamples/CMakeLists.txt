cmake_minimum_required(VERSION 3.2)
project(ZenUnitExamples)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

include_directories(${ZenUnitIncludeDirectory})
include_directories(${ZenMockIncludeDirectory})

file(GLOB Sources *.h *.cpp)
source_group("" FILES ${Sources})

add_executable(ZenUnitExamples ${Sources})

if(UNIX)
   target_link_libraries(ZenUnitExamples stdc++fs)
   if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
      target_link_libraries(ZenUnitExamples c++experimental)
   endif()
endif()

EnablePrecompiledHeaders()
IfMSVCAddRunTestsPostBuildStep()

if(MSVC)
   replace(CMAKE_CXX_FLAGS "/Wall" "/W4")
endif()
