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

macro(ConfigurePlatformSpecificPrecompiledHeaders)
   if(UNIX OR APPLE)
      if(ClangSanitizerMode_AddressAndUndefinedBehavior)
         set(SanitizerArgs "-fsanitize=address,undefined")
      elseif(ClangSanitizerMode_Thread)
         set(SanitizerArgs "-fsanitize=thread")
      else()
         set(SanitizerArgs "")
      endif()
      set(PchDotHFilePath "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/pch.h")
      if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
         if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            add_custom_target(${PROJECT_NAME}Pch ${CMAKE_CXX_COMPILER}
               -std=c++17 -Wall -Wextra -Werror -pthread -Wno-pragma-once-outside-header -pedantic -Wno-gnu-zero-variadic-macro-arguments -g
               ${SanitizerArgs} -I${CMAKE_SOURCE_DIR} -I${ZenUnitIncludeDirectory} -x c++-header ${PchDotHFilePath})
         elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
            add_custom_target(${PROJECT_NAME}Pch ${CMAKE_CXX_COMPILER}
               -std=c++17 -Wall -Wextra -Werror -pthread -Wno-pragma-once-outside-header -pedantic -Wno-gnu-zero-variadic-macro-arguments -O2
               ${SanitizerArgs} -I${CMAKE_SOURCE_DIR} -I${ZenUnitIncludeDirectory} -x c++-header ${PchDotHFilePath})
         endif()
         append(CMAKE_CXX_FLAGS "-include-pch ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/pch.h.gch")
      elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
         if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            add_custom_target(${PROJECT_NAME}Pch ${CMAKE_CXX_COMPILER}
               -std=c++17 -Wall -Wextra -Werror -pthread -Wno-attributes -g
               ${SanitizerArgs} -I${CMAKE_SOURCE_DIR} -I${ZenUnitIncludeDirectory} -x c++-header ${PchDotHFilePath})
         elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
            add_custom_target(${PROJECT_NAME}Pch ${CMAKE_CXX_COMPILER}
               -std=c++17 -Wall -Wextra -Werror -pthread -Wno-attributes -DNDEBUG -O2
               ${SanitizerArgs} -I${CMAKE_SOURCE_DIR} -I${ZenUnitIncludeDirectory} -x c++-header ${PchDotHFilePath})
         endif()
      endif()
      add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}Pch)
   elseif(MSVC)
      set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/Yupch.h")
      set_source_files_properties(pch.cpp PROPERTIES COMPILE_FLAGS "/Yc")
   endif()
endmacro()

macro(OnWindowsAddPostBuildStepToRunTests)
   if(MSVC)
      add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND $(TargetPath) --random-test-ordering --always-exit-0)
   endif()
endmacro()

