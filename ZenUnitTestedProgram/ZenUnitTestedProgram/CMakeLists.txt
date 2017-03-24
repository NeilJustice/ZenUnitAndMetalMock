cmake_minimum_required(VERSION 3.5)
project(ZenUnitTestedProgram)

include_directories(${CMAKE_SOURCE_DIR})
source_group("" FILES Main.cpp)

add_executable(ZenUnitTestedProgram Main.cpp)
target_link_libraries(ZenUnitTestedProgram StaticLibrary)

install(TARGETS ZenUnitTestedProgram DESTINATION ".")
