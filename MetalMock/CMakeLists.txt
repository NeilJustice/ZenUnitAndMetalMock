cmake_minimum_required(VERSION 3.2)
project(MetalMock)

source_group("" FILES MetalMock.h)

# Adds a fake static library for single-header MetalMock.h so that MetalMock appears as a Visual Studio project
add_library(MetalMock MetalMock.h)

set_target_properties(MetalMock PROPERTIES LINKER_LANGUAGE CXX)

install(DIRECTORY .
        DESTINATION include/MetalMock
        FILES_MATCHING REGEX "MetalMock.h"
        PATTERN REGEX "CMakeFiles|Debug|Release|RelWithDebInfo|MinSizeRel|MetalMock.dir" EXCLUDE)

if(UNIX)
   if(CodeCovMode)
     target_link_libraries(MetalMock CodeCovLibraryInterface)
   endif()
endif()
