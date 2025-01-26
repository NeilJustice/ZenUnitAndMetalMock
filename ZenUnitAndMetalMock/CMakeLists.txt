cmake_minimum_required(VERSION 3.20)
project(ZenUnitAndMetalMock)

file(GLOB_RECURSE sourceFilePaths ZenUnit.h MetalMock.h)
source_group("" FILES ${sourceFilePaths})

if(MSVC)
   add_library(ZenUnitAndMetalMock INTERFACE ${sourceFilePaths})
else()
   add_library(ZenUnitAndMetalMock INTERFACE)
endif()

install(DIRECTORY .
        DESTINATION "include/ZenUnitAndMetalMock/ZenUnitAndMetalMock"
        FILES_MATCHING REGEX "ZenUnit.h|MetalMock.h"
        PATTERN REGEX "CMakeFiles|Debug|Release|RelWithDebInfo|MinSizeRel|x64|ZenUnit.dir" EXCLUDE)

if(UNIX)
   add_custom_target(clean_installed_files COMMAND
      rm -rf /usr/local/include/ZenUnitAndMetalMock)
elseif(MSVC)
   add_custom_target(clean_installed_files COMMAND
      del /S /Q C:\\include\\ZenUnitAndMetalMock &&
      rmdir /S /Q C:\\include\\ZenUnitAndMetalMock)
endif()
