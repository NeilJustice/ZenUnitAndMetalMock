import os
import platform
import sys
sys.path.append('ZenUnitPy') # Jenkins
sys.path.append('../ZenUnitPy') # Jenkins
from ZenUnitPy import ArgParser, CMake, Process, Util, FileSystem

def main(args):
   if len(args) != 5:
      Util.print_and_exit(
'Invalid args: ' + ' '.join(args) + '\n' +
"""Usage: python3 BuildZenUnit.py --generator=<CMakeGenerator> --buildType=<CMakeBuildType> --definitions=<QuotedSpaceSeparatedCMakeDefinitions> --installDirectory=<DirectoryOrNoInstall>""", 1)
   else:
      cmakeGenerator = ArgParser.parse_arg('--generator', args[1])
      cmakeBuildType = ArgParser.parse_arg('--buildType', args[2])
      cmakeDefinitions = ArgParser.parse_arg('--definitions', args[3])
      installDirectory = ArgParser.parse_arg('--installDirectory', args[4])
      platformSystem = platform.system().casefold()
      if platformSystem == 'linux':
         linux_cmake_and_build(cmakeGenerator, cmakeBuildType, cmakeDefinitions, installDirectory)
         Process.run('ZenUnitTests/ZenUnitTests')
         optionally_install(cmakeBuildType, installDirectory)
         os.chdir('..')
      else:
         windows_cmake_and_build(cmakeGenerator, cmakeBuildType, cmakeDefinitions, installDirectory)
         optionally_install(cmakeBuildType, installDirectory)

def linux_cmake_and_build(cmakeGenerator, cmakeBuildType, cmakeDefinitions, installDirectory):
   casefoldedInstallDirectory = installDirectory.casefold()
   if casefoldedInstallDirectory != 'noinstall':
      cmakeDefinitions = f'{cmakeDefinitions} -DCMAKE_INSTALL_PREFIX={installDirectory}'
   CMake.generate(cmakeBuildType, cmakeGenerator, cmakeBuildType, cmakeDefinitions, '..')
   Process.run('ninja -v')

def optionally_install(cmakeBuildType, installDirectory):
   casefoldedInstallDirectory = installDirectory.casefold()
   if casefoldedInstallDirectory != 'noinstall':
      zenUnitInstallDirectory = os.path.join(installDirectory, 'include', 'ZenUnit')
      FileSystem.delete_folder_if_exists(zenUnitInstallDirectory)
      installCommand = f'cmake --build . --target install --config {cmakeBuildType}'
      Process.run(installCommand)

def windows_cmake_and_build(cmakeGenerator, cmakeBuildType, cmakeDefinitions, installDirectory):
   casefoldedInstallDirectory = installDirectory.casefold()
   if casefoldedInstallDirectory != 'noinstall':
      cmakeDefinitions = f'{cmakeDefinitions} -DCMAKE_INSTALL_PREFIX={installDirectory}'
   CMake.generate('.', cmakeGenerator, cmakeBuildType, cmakeDefinitions, '.')
   buildCommand = f'cmake --build . --config {cmakeBuildType}'
   Process.run(buildCommand)

if __name__ == "__main__": # pragma nocover
   main(sys.argv)
