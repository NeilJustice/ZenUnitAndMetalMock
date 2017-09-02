cmake_minimum_required(VERSION 3.2)
project(Executable)

include_directories(${CMAKE_SOURCE_DIR})

file(GLOB Sources *.h *.cpp)
source_group("" FILES ${Sources})

add_executable(Executable ${Sources})
target_link_libraries(Executable StaticLibrary)
