macro(append variable value)
   set(${variable} "${${variable}} ${value}")
endmacro()

macro(replace variable str replacement)
   string(REPLACE "${str}" "${replacement}" ${variable} ${${variable}})
endmacro()

macro(folder_source_group folderName)
   file(GLOB ${folderName}Files ${folderName}/*.*)
   source_group(${folderName} FILES ${${folderName}Files})
endmacro()

macro(folder_source_group_subfolder folderName subfolderName)
   file(GLOB ${folderName}${subfolderName}Files ${folderName}/${subfolderName}/*.*)
   source_group(${folderName}\\${subfolderName} FILES ${${folderName}${subfolderName}Files})
endmacro()

macro(folder_source_group_subsubfolder folderName subfolderName subsubFolderName)
   file(GLOB ${folderName}${subfolderName}${subsubFolderName}Files ${folderName}/${subfolderName}/${subsubFolderName}/*.*)
   source_group(${folderName}\\${subfolderName}\\${subsubFolderName} FILES ${${folderName}${subfolderName}${subsubFolderName}Files})
endmacro()

if(UNIX)
   if(NOT CMAKE_BUILD_TYPE)
      set(CMAKE_BUILD_TYPE Debug)
   endif()
endif()

set(ZenUnitIncludeDirectory "${CMAKE_SOURCE_DIR}/ZenUnit")
if(UNIX)
   set(GoogleBenchmarkIncludeDirectory "/usr/local/include/GoogleBenchmark")
   set(GoogleBenchmarkLibraryPath "/usr/local/lib/GoogleBenchmark/libbenchmark${CMAKE_BUILD_TYPE}.a")
elseif(MSVC)
   set(GoogleBenchmarkIncludeDirectory "C:/include/GoogleBenchmark")
   set(GoogleBenchmarkLibraryPath "C:/lib/GoogleBenchmark/benchmark$(Configuration).lib")
endif()

macro(IfMSVCEnablePrecompiledHeaders)
   if(MSVC)
      set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/Yupch.h")
      set_source_files_properties(pch.cpp PROPERTIES COMPILE_FLAGS "/Yc")
   endif()
endmacro()

macro(IfMSVCAddPostBuildStepToRunTestsRandomly)
   if(MSVC)
      add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND $(TargetPath) --random)
   endif()
endmacro()
