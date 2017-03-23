cmake_minimum_required(VERSION 3.5)
project(StaticLibrary)

file(GLOB Sources *.h *.cpp)
source_group("" FILES ${Sources})

add_library(StaticLibrary ${Sources})
