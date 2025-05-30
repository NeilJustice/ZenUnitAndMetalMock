cmake_minimum_required(VERSION 3.20)
project(ZenUnitLibraryTests)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${ZenUnitIncludeDirectory})
if(EXISTS ${GoogleBenchmarkIncludeDirectory})
   include_directories(${GoogleBenchmarkIncludeDirectory})
endif()

folder_source_group_subfolder(Components Args)
folder_source_group_subsubfolder(Components Args MetalMock)
folder_source_group_subfolder(Components Console)
folder_source_group_subsubfolder(Components Console MetalMock)
folder_source_group_subfolder(Components Misc)
folder_source_group_subsubfolder(Components Misc MetalMock)
folder_source_group_subfolder(Components TestRunners)
folder_source_group_subsubfolder(Components TestRunners MetalMock)
folder_source_group_subfolder(Components Tests)
folder_source_group_subsubfolder(Components Tests MetalMock)
folder_source_group_subfolder(Components TestResults)
folder_source_group_subfolder(Components Time)
folder_source_group_subsubfolder(Components Time MetalMock)
folder_source_group(Constants)
folder_source_group(Testing)
folder_source_group_subfolder(ValueTypes Anomaly)
folder_source_group_subfolder(ValueTypes Args)
folder_source_group_subsubfolder(ValueTypes Args MetalMock)
folder_source_group_subfolder(ValueTypes Console)
folder_source_group_subfolder(ValueTypes TestResults)
folder_source_group_subsubfolder(ValueTypes TestResults MetalMock)
folder_source_group_subfolder(ValueTypes Tests)
folder_source_group_subfolder(StaticComponents ToStringer)
folder_source_group_subsubfolder(StaticComponents ToStringer TypeTraits)
folder_source_group_subsubfolder(StaticComponents ToStringer ZenUnitPrinter)
folder_source_group(StaticUtilities)
folder_source_group(EqualizersAndRandoms)
folder_source_group_subfolder(EqualizersAndRandoms Equalizers)
folder_source_group_subfolder(EqualizersAndRandoms Random)

source_group("" FILES ZenUnitLibraryTestsMain.cpp IfWindowsIgnoreTheseWarningGlobally.h pch.h pch.cpp)
file(GLOB_RECURSE sourceFilePaths *.h *.cpp)

add_executable(ZenUnitLibraryTests ${sourceFilePaths})
target_link_libraries(ZenUnitLibraryTests ZenUnitTestUtils)

if(EXISTS ${GoogleBenchmarkLibraryPath})
   target_link_libraries(MetalMockTests ${GoogleBenchmarkLibraryPath})
endif()
if(MSVC)
   target_link_libraries(ZenUnitLibraryTests shlwapi)
endif()

if(UNIX)
   if(NOT IncludeWhatYouUseMode)
      target_precompile_headers(ZenUnitLibraryTests PRIVATE pch.h)
      set_target_properties(ZenUnitLibraryTests PROPERTIES UNITY_BUILD ON)
      set_target_properties(ZenUnitLibraryTests PROPERTIES UNITY_BUILD_BATCH_SIZE 30)
   endif()
elseif(MSVC)
   IfMSVCEnablePrecompiledHeaders()
   set_target_properties(ZenUnitLibraryTests PROPERTIES UNITY_BUILD ON)
   set_target_properties(ZenUnitLibraryTests PROPERTIES UNITY_BUILD_BATCH_SIZE 3)
   append(CMAKE_CXX_FLAGS "/FIpch.h")
   IfMSVCAddPostBuildStepToRunTests()
endif()

if(UNIX)
   if(LCovCodeCoverageMode)
     target_link_libraries(ZenUnitLibraryTests CodeCovLibraryInterface)
   endif()
endif()
