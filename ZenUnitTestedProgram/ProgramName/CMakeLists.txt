cmake_minimum_required(VERSION 3.5)
project(ProgramName)

include_directories(${CMAKE_SOURCE_DIR})

file(GLOB Sources *.h *.cpp)
source_group("" FILES ${Sources})

add_executable(ProgramName ${Sources})
target_link_libraries(ProgramName LibraryName)

install(TARGETS ProgramName DESTINATION ".")

