cmake_minimum_required(VERSION 3.2)
project(ZenUnitAndZenMock)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

if(UNIX)
   set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra -Werror -pthread -Wno-unused-parameter")
   if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
      append(CMAKE_CXX_FLAGS "-pedantic -Wno-gnu-zero-variadic-macro-arguments")
   elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
      append(CMAKE_CXX_FLAGS "-Wno-attributes -Wno-nonnull")
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
   # /Zc:rvalueCast : Enforce type conversion rules
   set(CMAKE_CXX_FLAGS "/EHsc /MP /sdl /std:c++17 /Wall /WX /Zc:rvalueCast")
   replace(CMAKE_EXE_LINKER_FLAGS_DEBUG "/debug" "/debug:fastlink")
   replace(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "/debug" "/debug:fastlink")
   replace(CMAKE_CXX_FLAGS_RELEASE "/O2" "/Od")
   replace(CMAKE_CXX_FLAGS_RELEASE "/Ob2" "/Ob0")
   set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

# Travis CI OSX tries to build header-only ZenUnit and ZenMock into a static library .a files
if(NOT APPLE)
   add_subdirectory(ZenUnit)
   add_subdirectory(ZenMock)
endif()
add_subdirectory(ZenUnitUtilsAndAssertionTests)
add_subdirectory(ZenUnitExamples)
add_subdirectory(ZenUnitLibraryTests)
add_subdirectory(ZenUnitTestUtils)
add_subdirectory(ZenUnitCompileSpeed)
add_subdirectory(ZenMockExamples)
add_subdirectory(ZenMockTests)

# CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true makes CMake command
# "cmake --build . --target install --config Debug/Release"
# just install ZenUnit.h and ZenMock.h without also building all other ZenUnit test executables
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)

if(UNIX)
   include(ProcessorCount)
   ProcessorCount(NumberOfCores)
   add_custom_target(clang-tidy COMMAND
      find -name "*.cpp" -print0 | xargs -0 -n 1 -P ${NumberOfCores} -t
      clang-tidy -header-filter=.* -p ${CMAKE_BUILD_TYPE}
         WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} VERBATIM USES_TERMINAL)
   add_dependencies(clang-tidy ZenUnitUtilsAndAssertionTestsPch ZenUnitExamplesPch ZenUnitLibraryTestsPch ZenUnitTestUtilsPch)
endif()
