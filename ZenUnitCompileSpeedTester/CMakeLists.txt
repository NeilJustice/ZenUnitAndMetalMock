cmake_minimum_required(VERSION 3.2)
project(ZenUnitCompileSpeedTester)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${ZenUnitIncludeDirectory})

file(GLOB_RECURSE sourceFilePaths *.h *.cpp)
source_group("" FILES ${sourceFilePaths})

add_executable(ZenUnitCompileSpeedTester ${sourceFilePaths})

target_link_libraries(ZenUnitCompileSpeedTester)
if(UNIX)
   target_link_libraries(ZenUnitCompileSpeedTester stdc++fs)
endif()

ConfigurePlatformSpecificPrecompiledHeaders()

if(UNIX)
   if(CodeCovMode)
     target_link_libraries(ZenUnitCompileSpeedTester CodeCovLibraryInterface)
   endif()
endif()
