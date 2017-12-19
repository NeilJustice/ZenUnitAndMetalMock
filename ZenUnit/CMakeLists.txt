cmake_minimum_required(VERSION 3.2)
project(ZenUnit)

include_directories(${CMAKE_SOURCE_DIR})
file(GLOB Sources *.h *.cpp)
source_group("" FILES ${Sources})
add_library(ZenUnit ${Sources})

install(DIRECTORY .
        DESTINATION include/ZenUnit/ZenUnit
        FILES_MATCHING REGEX "ZenUnit.h|ZenMock.h"
        PATTERN REGEX "CMakeFiles|Release|RelWithDebInfo|MinSizeRel|ZenUnit.dir" EXCLUDE)
