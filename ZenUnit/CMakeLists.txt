cmake_minimum_required(VERSION 3.2)
project(ZenUnit)
include(${CMAKE_SOURCE_DIR}/ZenUnitHelloWorld/CMakeMacros.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_SOURCE_DIR})
folder_source_group(Anomaly)
folder_source_group(Args)
folder_source_group(Console)
folder_source_group(Enums)
folder_source_group(Equalizers)
folder_source_group(Macros)
folder_source_group(Registration)
folder_source_group(Results)
folder_source_group(TestRunners)
folder_source_group(Tests)
folder_source_group(ToStringer)
folder_source_group_subfolder(ToStringer ZenUnitPrinter)
folder_source_group_subfolder(ToStringer SFINAE)
folder_source_group(Utils)
folder_source_group_subfolder(Utils Concurrency)
folder_source_group_subfolder(Utils Iteration)
folder_source_group_subfolder(Utils Time)
folder_source_group(ZenMock)
folder_source_group_subfolder(ZenMock 0)
folder_source_group_subfolder(ZenMock 1)
folder_source_group_subfolder(ZenMock 2)
folder_source_group_subfolder(ZenMock 3)
folder_source_group_subfolder(ZenMock 4)
folder_source_group_subfolder(ZenMock 5)
folder_source_group_subfolder(ZenMock 6)
folder_source_group_subfolder(ZenMock 7)
folder_source_group_subfolder(ZenMock 8)
folder_source_group_subfolder(ZenMock 9)
folder_source_group_subfolder(ZenMock 10)
folder_source_group_subfolder(ZenMock Exceptions)
file(GLOB TopLevelFiles *.h *.cpp)
source_group("" FILES ${TopLevelFiles})
file(GLOB_RECURSE Sources *.h *.cpp)

add_library(ZenUnit ${Sources})

EnablePrecompiledHeaders()

install(DIRECTORY .
        CONFIGURATIONS Debug
        DESTINATION include/ZenUnit/ZenUnit
        FILES_MATCHING REGEX "\\.h$|\\.cpp$"
        PATTERN REGEX "pch.h|pch.cpp|CMakeFiles|Release|RelWithDebInfo|MinSizeRel|ZenUnit.dir" EXCLUDE)

set_target_properties(ZenUnit PROPERTIES DEBUG_OUTPUT_NAME "ZenUnitDebug")
set_target_properties(ZenUnit PROPERTIES RELEASE_OUTPUT_NAME "ZenUnitRelease")
set_target_properties(ZenUnit PROPERTIES RELWITHDEBINFO_OUTPUT_NAME "ZenUnitRelWithDebInfo")
set_target_properties(ZenUnit PROPERTIES MINSIZEREL_OUTPUT_NAME "ZenUnitMinSizeRel")
install(TARGETS ZenUnit DESTINATION "lib/ZenUnit")

if(MSVC)
   append(CMAKE_CXX_FLAGS "/FdZenUnit.dir/$(Configuration)/ZenUnit$(Configuration).pdb")
   install(FILES ZenUnit.dir/Debug/ZenUnitDebug.pdb
           CONFIGURATIONS Debug
           DESTINATION "lib/ZenUnit")
   install(FILES ZenUnit.dir/RelWithDebInfo/ZenUnitRelWithDebInfo.pdb
           CONFIGURATIONS RelWithDebInfo
           DESTINATION "lib/ZenUnit")
endif()
