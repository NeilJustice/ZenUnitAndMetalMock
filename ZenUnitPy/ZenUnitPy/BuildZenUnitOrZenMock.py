import os
import platform
import sys
sys.path.append('ZenUnitPy') # Jenkins
sys.path.append('../ZenUnitPy') # Jenkins
sys.path.append('../ZenUnit/ZenUnitPy') # ZenMock
from ZenUnitPy import ArgParser, CMake, Process, Util

def main(args):
   if len(args) != 5:
      Util.print_and_exit(
'Invalid args: ' + ' '.join(args) + '\n'
"""Usage: python3 BuildZenUnitOrZenMock.py --zenunit-or-zenmock=<ZenUnitOrZenMock> --cmake-generator=<CMakeGenerator> --cmake-build-type=<CMakeBuildType> --cmake-definitions=<QuotedSpaceSeparatedCMakeDefinitions>""", 1)
   else:
      zenUnitOrZenMock = ArgParser.parse_arg('--zenunit-or-zenmock', args[1])
      cmakeGenerator = ArgParser.parse_arg('--cmake-generator', args[2])
      cmakeBuildType = ArgParser.parse_arg('--cmake-build-type', args[3])
      cmakeDefinitions = ArgParser.parse_arg('--cmake-definitions', args[4])
      platformSystem = platform.system().casefold()
      if platformSystem == 'linux':
         linux_cmake_and_build(cmakeGenerator, cmakeBuildType, cmakeDefinitions)
         if zenUnitOrZenMock == 'ZenMock':
            Process.run(f'ZenMockTests/ZenMockTests')
         else:
            Process.run(f'ZenUnitLibraryTests/ZenUnitLibraryTests')
            Process.run(f'ZenUnitUtilsAndAssertionTests/ZenUnitUtilsAndAssertionTests')
         os.chdir('..')
      else:
         windows_cmake_and_build(cmakeGenerator, cmakeBuildType, cmakeDefinitions)

def linux_cmake_and_build(cmakeGenerator, cmakeBuildType, cmakeDefinitions):
   CMake.generate(cmakeBuildType, cmakeGenerator, cmakeBuildType, cmakeDefinitions, '..')
   Process.run('ninja -v')

def windows_cmake_and_build(cmakeGenerator, cmakeBuildType, cmakeDefinitions):
   CMake.generate('.', cmakeGenerator, cmakeBuildType, cmakeDefinitions, '.')
   buildCommand = f'cmake --build . --config {cmakeBuildType}'
   Process.run(buildCommand)

if __name__ == "__main__": # pragma nocover
   main(sys.argv)
