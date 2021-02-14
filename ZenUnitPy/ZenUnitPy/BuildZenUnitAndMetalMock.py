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
         Process.run('MetalMockExamples/MetalMockExamples')
         Process.run('MetalMockTests/MetalMockTests')
         Process.run('ZenUnitCompileSpeedTests/ZenUnitCompileSpeedTests')
         Process.run('ZenUnitExamples/ZenUnitExamples')
         Process.run('ZenUnitLibraryTests/ZenUnitLibraryTests')
         Process.run('ZenUnitUtilsAndAssertionTests/ZenUnitUtilsAndAssertionTests')
         os.chdir('..')
      else:
         windows_cmake_build(cmakeGenerator, cmakeBuildType, cmakeDefinitions)
   return 0

def linux_cmake_build(cmakeGenerator, cmakeBuildType, cmakeDefinitions):
   CMake.generate(cmakeBuildType, cmakeGenerator, cmakeBuildType, cmakeDefinitions, '..')
   Process.run('ninja -v')

def windows_cmake_build(cmakeGenerator, cmakeBuildType, cmakeDefinitions):
   CMake.generate('.', cmakeGenerator, cmakeBuildType, cmakeDefinitions, '.')
   buildCommand = f'cmake --build . --config {cmakeBuildType}'
   Process.run(buildCommand)

if __name__ == "__main__": # pragma nocover
   main(sys.argv)

# Example command line arguments:
# --cmake-generator="Visual Studio 16 2019" --cmake-build-type=Debug --cmake-definitions=""
# Working directory:
# C:\Code\ZenUnitAndMetalMock
