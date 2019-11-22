cmake_minimum_required(VERSION 3.2)
project(ZenMock)

source_group("" FILES ZenMock.h)

# Adds a fake static library for single-header ZenMock.h so that ZenMock appears as a Visual Studio project
add_library(ZenMock ZenMock.h)

set_target_properties(ZenMock PROPERTIES LINKER_LANGUAGE CXX)

install(DIRECTORY .
        DESTINATION include/ZenMock
        FILES_MATCHING REGEX "ZenMock.h"
        PATTERN REGEX "CMakeFiles|Debug|Release|RelWithDebInfo|MinSizeRel|ZenMock.dir" EXCLUDE)

if(UNIX)
   if(CodeCovMode)
     target_link_libraries(ZenMock CodeCovLibraryInterface)
   endif()
endif()
