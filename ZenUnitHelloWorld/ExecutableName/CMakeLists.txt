cmake_minimum_required(VERSION 3.5)
project(ExecutableName)

include_directories(${CMAKE_SOURCE_DIR})

file(GLOB Sources *.h *.cpp)
source_group("" FILES ${Sources})

add_executable(ExecutableName ${Sources})
target_link_libraries(ExecutableName LibraryName)

install(TARGETS ExecutableName DESTINATION ".")

