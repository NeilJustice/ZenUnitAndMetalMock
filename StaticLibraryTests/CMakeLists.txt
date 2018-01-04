cmake_minimum_required(VERSION 3.2)
project(StaticLibraryTests)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

replace(CMAKE_CXX_FLAGS "/Wall" "/W4")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(
   ${CMAKE_SOURCE_DIR}
   ${ZenUnitIncludeDirectory})

folder_source_group(Mock)
folder_source_group(ZenUnit)

file(GLOB_RECURSE Sources *.h *.cpp)
source_group("" FILES ${Sources})

add_executable(StaticLibraryTests ${Sources})
target_link_libraries(StaticLibraryTests StaticLibrary)

EnablePrecompiledHeaders()
IfMSVCAddRunTestsPostBuildStep()
