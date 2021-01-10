cmake_minimum_required(VERSION 3.2)
project(ZenUnitAndMetalMock)

file(GLOB_RECURSE sourceFilePaths ZenUnit.h MetalMock.h)
source_group("" FILES ${sourceFilePaths})

add_library(ZenUnitAndMetalMock INTERFACE ${sourceFilePaths})

install(DIRECTORY .
        DESTINATION include/ZenUnit/ZenUnit
        FILES_MATCHING REGEX "ZenUnit.h|MetalMock.h"
        PATTERN REGEX "CMakeFiles|Debug|Release|RelWithDebInfo|MinSizeRel|ZenUnit.dir" EXCLUDE)
