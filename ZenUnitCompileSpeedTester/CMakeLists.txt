cmake_minimum_required(VERSION 3.2)
project(ZenUnitCompileSpeedTester)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

include_directories(${ZenUnitIncludeDirectory})

source_group("" FILES ZenUnitCompileSpeedTesterMain.cpp)

file(GLOB_RECURSE Sources *.h *.cpp)

add_executable(ZenUnitCompileSpeedTester ${Sources})
target_link_libraries(ZenUnitCompileSpeedTester)
if(UNIX)
   target_link_libraries(ZenUnitCompileSpeedTester stdc++fs)
endif()

if(UNIX)
   if(CodeCovMode)
     target_link_libraries(ZenUnitCompileSpeedTester CodeCovLibraryInterface)
   endif()
endif()
