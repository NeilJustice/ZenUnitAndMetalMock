cmake_minimum_required(VERSION 3.5)
project(StaticLibrary.Test)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.txt)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${ZenUnitIncludeDirectory})

file(GLOB Sources *.h *.cpp)
source_group("" FILES ${Sources})

add_executable(StaticLibrary.Test ${Sources})
target_link_libraries(StaticLibrary.Test StaticLibrary ${ZenUnitLibraryPath})

if(MSVC)
   set_target_properties(StaticLibrary.Test PROPERTIES COMPILE_FLAGS "/Yupch.h")
   set_source_files_properties(pch.cpp PROPERTIES COMPILE_FLAGS "/Yc")
   add_custom_command(TARGET StaticLibrary.Test POST_BUILD COMMAND $(TargetPath) -exit0)
endif()
