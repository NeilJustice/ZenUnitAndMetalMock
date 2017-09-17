import os
import platform
import sys
sys.path.append('ZenUnitPy') # Jenkins
sys.path.append('../ZenUnitPy') # Jenkins
from ZenUnitPy import CMake, Process, Util

def main(args):
   if len(args) != 5:
      Util.print_and_exit(
'Invalid args: ' + ' '.join(args) + '\n' +
"""Usage: python3 CMakeBuildZenUnit.py --generator=<CMakeGenerator> --buildType=<CMakeBuildType> --definitions=<QuotedSpaceSeparatedCMakeDefinitions> --installDirectory=<DirectoryOrNoInstall>""", 1)
   else:
      generator = args[1]
      buildType = args[2]
      definitions = args[3]
      installDirectory = args[4]
      platformSystem = platform.system().casefold()
      if platformSystem == 'linux':
         linux_cmake_and_build(generator, buildType, definitions)
         linux_run_zenunit_tests('ZenUnitTests')
         optionally_install(buildType, installDirectory)
         os.chdir('..')
      else:
         windows_cmake_and_build(generator, buildType, definitions)
         windows_run_zenunit_tests(buildType, 'ZenUnitTests')
         optionally_install(buildType, installDirectory)

def linux_cmake_and_build(generator, buildType, definitions):
   CMake.generate(buildType, generator, buildType, definitions, '..')
   Process.run('ninja -v')

def linux_run_zenunit_tests(testsProjectName):
   Process.run(f'{testsProjectName}/{testsProjectName}')

def optionally_install(buildType, installDirectory):
   casefoldedInstallDirectory = installDirectory.casefold()
   if casefoldedInstallDirectory != 'noinstall':
      installCommand = f'cmake --build . --target install --config {buildType}'
      Process.run(installCommand)

def windows_cmake_and_build(generator, buildType, definitions):
   CMake.generate('.', generator, buildType, definitions, '.')
   buildCommand = f'cmake --build . --config {buildType}'
   Process.run(buildCommand)

def windows_run_zenunit_tests(buildType, testsProjectName):
   runTestsCommand = f'{testsProjectName}/{buildType}/{testsProjectName}.exe'
   Process.run(runTestsCommand)

if __name__ == "__main__": # pragma nocover
   main(sys.argv)
