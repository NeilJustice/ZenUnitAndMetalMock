cmake_minimum_required(VERSION 3.5)
project(Examples.Test)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.txt)

include_directories(${CMAKE_SOURCE_DIR})
file(GLOB Sources *.h *.cpp)
source_group("" FILES ${Sources})

add_executable(Examples.Test ${Sources})
target_link_libraries(Examples.Test ZenUnit Examples)

if(UNIX)
   EnableClangOrGCCPrecompiledHeaders()
elseif(MSVC)
   replace(CMAKE_CXX_FLAGS "/Wall" "/W4")
   EnableMSVCPrecompiledHeaders()
endif()
