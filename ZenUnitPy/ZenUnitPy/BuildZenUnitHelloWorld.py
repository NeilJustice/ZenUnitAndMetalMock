import os
import platform
import sys
sys.path.append('ZenUnitPy') # Jenkins
sys.path.append('../ZenUnitPy') # Jenkins
from ZenUnitPy import ArgParser, Util, BuildZenUnit, Process

def main(args):
   if len(args) != 4:
      Util.print_and_exit(
'Invalid args: ' + ' '.join(args) + '\n' +
"""Usage: python3 BuildZenUnitHelloWorld.py --generator=<CMakeGenerator> --buildType=<CMakeBuildType> --definitions=<QuotedSpaceSeparatedCMakeDefinitions>""", 1)
   else:
      cmakeGenerator = ArgParser.parse_arg('--generator', args[1])
      cmakeBuildType = ArgParser.parse_arg('--buildType', args[2])
      cmakeDefinitions = ArgParser.parse_arg('--definitions', args[3])
      casefoldedPlatformSystem = platform.system().casefold()
      if casefoldedPlatformSystem == 'linux':
         BuildZenUnit.linux_cmake_and_build(cmakeGenerator, cmakeBuildType, cmakeDefinitions)
         BuildZenUnit.linux_run_tests('ZenUnitHelloWorldTests')
         os.chdir('..')
      else:
         os.chdir('ZenUnitHelloWorld')
         BuildZenUnit.windows_cmake_and_build(cmakeGenerator, cmakeBuildType, cmakeDefinitions)
         Process.run(rf'StaticLibraryTests\{cmakeBuildType}\StaticLibraryTests.exe')

if __name__ == "__main__": # pragma nocover
   main(sys.argv)
