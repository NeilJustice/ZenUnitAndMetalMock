cmake_minimum_required(VERSION 3.5)
project(StaticLibrary.Test)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${ZenUnitIncludeDirectory})

folder_source_group(Mock)
file(GLOB_RECURSE Sources *.h *.cpp)
source_group("" FILES ${Sources})

add_executable(StaticLibrary.Test ${Sources})
target_link_libraries(StaticLibrary.Test StaticLibrary ${ZenUnitLibraryPath})

EnablePrecompiledHeaders()
IfMSVCAddRunTestsPostBuildStep()
