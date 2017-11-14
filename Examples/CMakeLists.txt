cmake_minimum_required(VERSION 3.2)
project(Examples)

file(GLOB Sources *.h *.cpp)
source_group("" FILES ${Sources})

add_library(Examples ${Sources})

if(MSVC)
   replace(CMAKE_CXX_FLAGS "/Wall" "/W4")
endif()

