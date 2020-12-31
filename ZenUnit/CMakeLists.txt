cmake_minimum_required(VERSION 3.2)
project(ZenUnit)

add_library(ZenUnit INTERFACE)

install(DIRECTORY .
        DESTINATION include/ZenUnit/ZenUnit
        FILES_MATCHING REGEX "ZenUnit.h|MetalMock.h"
        PATTERN REGEX "CMakeFiles|Debug|Release|RelWithDebInfo|MinSizeRel|ZenUnit.dir" EXCLUDE)

if(UNIX)
   if(CodeCovMode)
     target_link_libraries(ZenUnit CodeCovLibraryInterface)
   endif()
endif()
