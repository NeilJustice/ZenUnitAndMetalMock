import os
import platform
import sys
sys.path.append('ZenUnitPy') # Jenkins
sys.path.append('../ZenUnitPy') # Jenkins
sys.path.append('../ZenUnit/ZenUnitPy') # MetalMock
from ZenUnitPy import ArgParser, CMake, Process, Util

def main(args):
   if len(args) != 5:
      Util.print_and_exit(
'Invalid args: ' + ' '.join(args) + '\n'
"""Usage: python BuildAndInstallZenUnitAndMetalMock.py --cmake-generator=<CMakeGenerator> --cmake-architecture=<x64OrWin32> --cmake-build-type=<CMakeBuildType> --cmake-definitions=<QuotedSpaceSeparatedCMakeDefinitions>""", 1)
   else:
      cmakeGenerator = ArgParser.parse_arg('--cmake-generator', args[1])
      cmakeArch = ArgParser.parse_arg('--cmake-architecture', args[2])
      cmakeBuildType = ArgParser.parse_arg('--cmake-build-type', args[3])
      cmakeDefinitions = ArgParser.parse_arg('--cmake-definitions', args[4])
      platformSystem = platform.system().casefold()
      if platformSystem == 'linux':
         linux_cmake_build_install(cmakeGenerator, cmakeArch, cmakeBuildType, cmakeDefinitions)
         Process.run(f'MetalMockTests/MetalMockTests')
         Process.run(f'ZenUnitLibraryTests/ZenUnitLibraryTests')
         Process.run(f'ZenUnitUtilsAndAssertionTests/ZenUnitUtilsAndAssertionTests')
         os.chdir('..')
      else:
         windows_cmake_build_install(cmakeGenerator, cmakeArch, cmakeBuildType, cmakeDefinitions)

def linux_cmake_build_install(cmakeGenerator, cmakeArch, cmakeBuildType, cmakeDefinitions):
   CMake.generate(cmakeBuildType, cmakeGenerator, cmakeArch, cmakeBuildType, cmakeDefinitions, '..')
   Process.run('ninja -v')
   CMake.install()

def windows_cmake_build_install(cmakeGenerator, cmakeArch, cmakeBuildType, cmakeDefinitions):
   CMake.generate('.', cmakeGenerator, cmakeArch, cmakeBuildType, cmakeDefinitions, '.')
   buildCommand = f'cmake --build . --config {cmakeBuildType}'
   Process.run(buildCommand)
   CMake.install()

if __name__ == "__main__": # pragma nocover
   main(sys.argv)
