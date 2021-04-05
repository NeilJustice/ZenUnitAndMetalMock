import os
import platform
import sys
from ZenUnitPy import ArgParser, CMake, Process, Util

def main(args):
   if len(args) != 4:
      Util.print_and_exit(
'Invalid args: ' + ' '.join(args) + '\n'
"""Usage: python BuildZenUnitAndMetalMock.py --cmake-generator=<CMakeGenerator> --cmake-build-type=<CMakeBuildType> --cmake-definitions=<QuotedSpaceSeparatedCMakeDefinitions>""", 1)
   else:
      cmakeGenerator = ArgParser.parse_arg('--cmake-generator', args[1])
      cmakeBuildType = ArgParser.parse_arg('--cmake-build-type', args[2])
      cmakeDefinitions = ArgParser.parse_arg('--cmake-definitions', args[3])
      platformSystem = platform.system().casefold()
      if platformSystem == 'linux':
         linux_cmake_build(cmakeGenerator, cmakeBuildType, cmakeDefinitions)
         Process.fail_fast_run('MetalMockExamples/MetalMockExamples --test-runs=2 --random')
         Process.fail_fast_run('MetalMockTests/MetalMockTests --test-runs=2 --random')
         Process.fail_fast_run('ZenUnitCompileSpeedTests/ZenUnitCompileSpeedTests --test-runs=2 --random')
         Process.fail_fast_run('ZenUnitExamples/ZenUnitExamples --test-runs=2 --random')
         Process.fail_fast_run('ZenUnitLibraryTests/ZenUnitLibraryTests --test-runs=2 --random')
         Process.fail_fast_run('ZenUnitUtilsAndAssertionTests/ZenUnitUtilsAndAssertionTests --test-runs=2 --random')
         os.chdir('..')
      else:
         windows_cmake_build(cmakeGenerator, cmakeBuildType, cmakeDefinitions) # Runs all tests once randomly as post-build events
         # Run all tests randomly a second time
         Process.fail_fast_run(f'MetalMockExamples/{cmakeBuildType}/MetalMockExamples.exe --random')
         Process.fail_fast_run(f'MetalMockTests/{cmakeBuildType}/MetalMockTests.exe --random')
         Process.fail_fast_run(f'ZenUnitCompileSpeedTests/{cmakeBuildType}/ZenUnitCompileSpeedTests.exe --random')
         Process.fail_fast_run(f'ZenUnitExamples/{cmakeBuildType}/ZenUnitExamples.exe --random')
         Process.fail_fast_run(f'ZenUnitLibraryTests/{cmakeBuildType}/ZenUnitLibraryTests.exe --random')
         Process.fail_fast_run(f'ZenUnitUtilsAndAssertionTests/{cmakeBuildType}/ZenUnitUtilsAndAssertionTests.exe --random')
   return 0

def linux_cmake_build(cmakeGenerator, cmakeBuildType, cmakeDefinitions):
   CMake.generate(cmakeBuildType, cmakeGenerator, cmakeBuildType, cmakeDefinitions, '..')
   Process.fail_fast_run('ninja -v')

def windows_cmake_build(cmakeGenerator, cmakeBuildType, cmakeDefinitions):
   CMake.generate('.', cmakeGenerator, cmakeBuildType, cmakeDefinitions, '.')
   cmakeBuildCommand = f'cmake.exe --build . --config {cmakeBuildType}'
   Process.fail_fast_run(cmakeBuildCommand)

if __name__ == "__main__": # pragma nocover
   main(sys.argv)

# Example command line arguments:
# --cmake-generator="Visual Studio 16 2019" --cmake-build-type=Debug --cmake-definitions=""
# Working directory:
# D:\Code\ZenUnitAndMetalMock
