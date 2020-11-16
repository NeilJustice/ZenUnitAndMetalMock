cmake_minimum_required(VERSION 3.2)
project(ZenUnit)

source_group("" FILES ZenUnit.h MetalMock.h)

# Adds a fake static library for single-header ZenUnit.h so that ZenUnit appears as a Visual Studio project
add_library(ZenUnit "ZenUnit.h" "MetalMock.h")

set_target_properties(ZenUnit PROPERTIES LINKER_LANGUAGE CXX)

install(DIRECTORY .
        DESTINATION include/ZenUnit/ZenUnit
        FILES_MATCHING REGEX "ZenUnit.h"
        PATTERN REGEX "CMakeFiles|Debug|Release|RelWithDebInfo|MinSizeRel|ZenUnit.dir" EXCLUDE)

install(DIRECTORY .
        DESTINATION include/ZenUnit/ZenUnit
        FILES_MATCHING REGEX "MetalMock.h"
        PATTERN REGEX "CMakeFiles|Debug|Release|RelWithDebInfo|MinSizeRel|ZenUnit.dir" EXCLUDE)

if(UNIX)
   if(CodeCovMode)
     target_link_libraries(ZenUnit CodeCovLibraryInterface)
   endif()
endif()
