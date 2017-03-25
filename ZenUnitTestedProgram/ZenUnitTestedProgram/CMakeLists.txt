cmake_minimum_required(VERSION 3.5)
project(ZenUnitTestedProgram)

include_directories(${CMAKE_SOURCE_DIR})

file(GLOB Sources *.h *.cpp)
source_group("" FILES ${Sources})

add_executable(ZenUnitTestedProgram ${Sources})
target_link_libraries(ZenUnitTestedProgram StaticLibrary)

install(TARGETS ZenUnitTestedProgram DESTINATION ".")
