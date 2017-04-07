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

macro(EnablePrecompiledHeaders)
   if(UNIX)
      if(AddressSanitizerMode)
         set(SanitizeAddressArg -fsanitize=address)
      endif()
      if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
         if(CMAKE_BUILD_TYPE STREQUAL "" OR CMAKE_BUILD_TYPE STREQUAL "Debug")
            add_custom_target(${PROJECT_NAME}Pch $ENV{CXX} -std=c++14 -Wall -Wextra -Werror -pthread
               -Wno-pragma-once-outside-header -pedantic -Wno-gnu-zero-variadic-macro-arguments
               ${SanitizeAddressArg} -I${CMAKE_SOURCE_DIR} -I/usr/local/include/ZenUnit -x c++-header ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/pch.h)
         elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
            add_custom_target(${PROJECT_NAME}Pch $ENV{CXX} -std=c++14 -Wall -Wextra -Werror -pthread -O3
               -Wno-pragma-once-outside-header -pedantic -Wno-gnu-zero-variadic-macro-arguments
               ${SanitizeAddressArg} -I${CMAKE_SOURCE_DIR} -I/usr/local/include/ZenUnit -x c++-header ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/pch.h)
         elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
            add_custom_target(${PROJECT_NAME}Pch $ENV{CXX} -std=c++14 -Wall -Wextra -Werror -pthread -O3 -g
               -Wno-pragma-once-outside-header -pedantic -Wno-gnu-zero-variadic-macro-arguments
               ${SanitizeAddressArg} -I${CMAKE_SOURCE_DIR} -I/usr/local/include/ZenUnit -x c++-header ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/pch.h)
         elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
            add_custom_target(${PROJECT_NAME}Pch $ENV{CXX} -std=c++14 -Wall -Wextra -Werror -pthread -Os
               -Wno-pragma-once-outside-header  -pedantic -Wno-gnu-zero-variadic-macro-arguments
               ${SanitizeAddressArg} -I${CMAKE_SOURCE_DIR} -I/usr/local/include/ZenUnit -x c++-header ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/pch.h)
         endif()
         append(CMAKE_CXX_FLAGS "-include-pch ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/pch.h.gch")
      elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
         if(CMAKE_BUILD_TYPE STREQUAL "" OR CMAKE_BUILD_TYPE STREQUAL "Debug")
            add_custom_target(${PROJECT_NAME}Pch $ENV{CXX} -std=c++14 -Wall -Wextra -Werror -pthread -g
               ${SanitizeAddressArg} -I${CMAKE_SOURCE_DIR} -I/usr/local/include/ZenUnit -x c++-header ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/pch.h)
         elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
            add_custom_target(${PROJECT_NAME}Pch $ENV{CXX} -std=c++14 -Wall -Wextra -Werror -pthread -O3 -DNDEBUG
               ${SanitizeAddressArg} -I${CMAKE_SOURCE_DIR} -I/usr/local/include/ZenUnit -x c++-header ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/pch.h)
         elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
            add_custom_target(${PROJECT_NAME}Pch $ENV{CXX} -std=c++14 -Wall -Wextra -Werror -pthread -O3 -DNDEBUG -g
               ${SanitizeAddressArg} -I${CMAKE_SOURCE_DIR} -I/usr/local/include/ZenUnit -x c++-header ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/pch.h)
         elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
            add_custom_target(${PROJECT_NAME}Pch $ENV{CXX} -std=c++14 -Wall -Wextra -Werror -pthread -Os -DNDEBUG
               ${SanitizeAddressArg} -I${CMAKE_SOURCE_DIR} -I/usr/local/include/ZenUnit -x c++-header ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/pch.h)
         endif()
      endif()
      add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}Pch)
   elseif(MSVC)
      set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/Yupch.h")
      set_source_files_properties(pch.cpp PROPERTIES COMPILE_FLAGS "/Yc")
   endif()
endmacro()

macro(IfMSVCAddRunTestsPostBuildStep)
   if(MSVC)
      add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND $(TargetPath) -exit0)
   endif()
endmacro()

if(UNIX)
   set(ZenUnitIncludeDirectory /usr/local/include/ZenUnit)
   set(ZenUnitLibraryPath /usr/local/lib/ZenUnit/libZenUnit${CMAKE_BUILD_TYPE}.a)
elseif(MSVC)
   set(ZenUnitIncludeDirectory C:\\install\\include\\ZenUnit)
   set(ZenUnitLibraryPath C:\\install\\lib\\ZenUnit\\ZenUnit$(Configuration).lib)
endif()
