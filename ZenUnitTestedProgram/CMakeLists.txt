cmake_minimum_required(VERSION 3.5)
project(ZenUnitTestedProgram)
include(CMakeMacros.cmake)

set(CMAKE_CONFIGURATION_TYPES Debug;Release;RelWithDebInfo)

if(UNIX)
   set(CMAKE_CXX_FLAGS "-std=c++1z -Wall -Wextra -Werror -pthread")
elseif(MSVC)
   set(CMAKE_CXX_FLAGS "/W4 /WX /EHsc /MP")
   replace(CMAKE_EXE_LINKER_FLAGS_DEBUG "/debug" "/debug:fastlink")
   set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

add_subdirectory(ZenUnitTestedProgram)
add_subdirectory(StaticLibrary)
add_subdirectory(StaticLibrary.Test)
