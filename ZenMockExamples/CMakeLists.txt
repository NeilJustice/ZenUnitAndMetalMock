cmake_minimum_required(VERSION 3.2)
project(ZenMockExamples)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

include_directories(${ZenUnitIncludeDirectory})
include_directories(${ZenMockIncludeDirectory})

file(GLOB_RECURSE Sources *.h *.cpp)
source_group("" FILES ${Sources})

add_executable(ZenMockExamples ${Sources})

if(UNIX)
   target_link_libraries(ZenMockExamples stdc++fs)
   if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
      target_link_libraries(ZenMockExamples c++experimental)
   endif()
endif()

EnablePrecompiledHeaders()
IfMSVCAddRunTestsPostBuildStep()
