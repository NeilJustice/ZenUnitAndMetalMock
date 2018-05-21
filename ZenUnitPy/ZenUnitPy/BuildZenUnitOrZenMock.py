import os
import platform
import sys
sys.path.append('ZenUnitPy') # Jenkins
sys.path.append('../ZenUnitPy') # Jenkins
sys.path.append('../ZenUnit/ZenUnitPy') # ZenMock
from ZenUnitPy import ArgParser, CMake, Process, Util, FileSystem

def main(args):
   if len(args) != 5:
      Util.print_and_exit(
'Invalid args: ' + ' '.join(args) + '\n' +
"""Usage: python3 BuildZenUnitOrZenMock.py --ZenUnitOrZenMock=<ZenUnitOrZenMock> --generator=<CMakeGenerator> --buildType=<CMakeBuildType> --definitions=<QuotedSpaceSeparatedCMakeDefinitions>""", 1)
   else:
      zenUnitOrZenMock = ArgParser.parse_arg('--ZenUnitOrZenMock', args[1])
      cmakeGenerator = ArgParser.parse_arg('--generator', args[2])
      cmakeBuildType = ArgParser.parse_arg('--buildType', args[3])
      cmakeDefinitions = ArgParser.parse_arg('--definitions', args[4])
      platformSystem = platform.system().casefold()
      if platformSystem == 'linux':
         linux_cmake_and_build(cmakeGenerator, cmakeBuildType, cmakeDefinitions)
         Process.run(f'{zenUnitOrZenMock}Tests/{zenUnitOrZenMock}Tests')
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
