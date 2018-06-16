cmake_minimum_required(VERSION 3.2)
project(ZenUnit)

include_directories(${CMAKE_SOURCE_DIR})
file(GLOB Sources *.h *.cpp)
source_group("" FILES ${Sources})

add_library(ZenUnit ${Sources})
set_target_properties(ZenUnit PROPERTIES LINKER_LANGUAGE CXX)

install(DIRECTORY .
        DESTINATION include/ZenUnit
        FILES_MATCHING REGEX "ZenUnit.h"
        PATTERN REGEX "CMakeFiles|Release|RelWithDebInfo|MinSizeRel|ZenUnit.dir" EXCLUDE)
