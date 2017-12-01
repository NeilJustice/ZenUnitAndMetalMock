cmake_minimum_required(VERSION 3.2)
project(ZenUnit)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

if(UNIX)
   set(CMAKE_CXX_FLAGS "-std=c++1z -Wall -Wextra -Werror -pthread -Wno-unused-parameter")
   if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
      append(CMAKE_CXX_FLAGS "-pedantic -Wno-gnu-zero-variadic-macro-arguments")
   elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
      append(CMAKE_CXX_FLAGS "-Wno-attributes")
   endif()
   option(ClangTidyMode "Sets CMAKE_EXPORT_COMPILE_COMMANDS to ON" OFF)
   option(SanitizersMode "Appends -fsanitize=address,undefined" OFF)
   option(ClangCoverageMode "Appends -fcoverage-mapping and -fprofile-instr-generate=coverage.profraw" OFF)
   if(ClangTidyMode)
      set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
      message("ClangTidyMode enabled: CMAKE_EXPORT_COMPILE_COMMANDS set to ON")
   elseif(SanitizersMode)
      append(CMAKE_CXX_FLAGS "-fsanitize=address,undefined")
      message("SanitizersMode enabled: -fsanitize=address,undefined appended to CMAKE_CXX_FLAGS")
   elseif(ClangCoverageMode)
      append(CMAKE_CXX_FLAGS "-fcoverage-mapping -fprofile-instr-generate=coverage.profraw")
      message("ClangCoverageMode enabled: -fcoverage-mapping -fprofile-instr-generate=coverage.profraw appended to CMAKE_CXX_FLAGS")
   endif()
elseif(MSVC)
   set(CMAKE_CXX_FLAGS "/std:c++latest /Wall /WX /EHsc /MP")
   replace(CMAKE_EXE_LINKER_FLAGS_DEBUG "/debug" "/debug:fastlink")
   replace(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "/debug" "/debug:fastlink")
   # Disable time-expensive release mode optimization
   # while ZenUnit is in pre-1.0 development
   replace(CMAKE_CXX_FLAGS_RELEASE "/O2" "/Od")
   set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

add_subdirectory(ZenUnit)
add_subdirectory(ZenUnitTests)
add_subdirectory(Examples)
add_subdirectory(ExamplesTests)
add_subdirectory(Executable)
add_subdirectory(StaticLibrary)
add_subdirectory(StaticLibraryTests)

# Allows CMake command "cmake --build . --target install --config Debug/Release"
# to just install ZenUnit and not also build ZenUnitTests
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)

if(UNIX)
   include(ProcessorCount)
   ProcessorCount(NumberOfCores)
   add_custom_target(clang-tidy COMMAND
      find -name "*.cpp" -print0 | xargs -0 -n 1 -P ${NumberOfCores} -t
      /usr/local/bin/clang-tidy -header-filter=.* -p ${CMAKE_BUILD_TYPE}
         WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} VERBATIM USES_TERMINAL)
   add_dependencies(clang-tidy ZenUnitPch ZenUnitTestsPch ExamplesTestsPch)
endif()
