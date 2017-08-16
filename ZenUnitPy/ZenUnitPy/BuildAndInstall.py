import os
import platform
import sys
sys.path.append('ZenUnitPy') # Jenkins
sys.path.append('../ZenUnitPy') # Jenkins
from ZenUnitPy import CMake, Process, Util

def main(args):
   if len(args) != 8:
      Util.print_and_exit(
'Invalid args: ' + ' '.join(args) + '\n' +
"""Usage: python BuildAndInstall.py
<CMakeGenerator>
<CMakeBuildType>
<StaticLibraryName>
<StaticLibraryTestName>
<ExpectedCommentSectionSubstring>
<CMakeDefinitions>
<Install|NoInstall>""", 1)
   else:
      cmakeGenerator = args[1]
      cmakeBuildType = args[2]
      staticLibraryName = args[3]
      staticLibraryTestName = args[4]
      expectedCommentSectionSubstring = args[5]
      cmakeDefinitions = args[6]
      installNoInstallString = args[7]
      doInstall = installNoInstallString == 'Install'
      if platform.system() == 'Linux':
         linux_cmake_and_build(cmakeGenerator, cmakeBuildType, staticLibraryName, cmakeDefinitions)
         linux_check_comment_section(cmakeBuildType, staticLibraryName, expectedCommentSectionSubstring)
         linux_runtests(cmakeBuildType, staticLibraryTestName)
         linux_install(cmakeBuildType, doInstall)
      else:
         windows_cmake_and_build(
            cmakeGenerator, cmakeBuildType, staticLibraryName, cmakeDefinitions)
         windows_runtests(cmakeBuildType, staticLibraryTestName)
         windows_install(cmakeBuildType, doInstall)

def linux_cmake_and_build(
   cmakeGenerator, cmakeBuildType, staticLibraryName, cmakeDefinitions):
   CMake.generate(cmakeBuildType, cmakeGenerator, cmakeBuildType, cmakeDefinitions, '..')
   Process.run('ninja -v')
   os.chdir('..')

def linux_check_comment_section(
   cmakeBuildType, staticLibraryName, expectedCommentSectionSubstring):
   if expectedCommentSectionSubstring:
      readelfCommand = 'readelf -p .comment {0}/{1}/lib{1}{0}.a'.format(cmakeBuildType, staticLibraryName)
      Process.run_and_check_stdout_for_substring(readelfCommand, expectedCommentSectionSubstring)

def linux_runtests(cmakeBuildType, staticLibraryTestName):
   runTestsCommand = '{0}/{1}/{1}'.format(cmakeBuildType, staticLibraryTestName)
   Process.run(runTestsCommand)

def linux_install(cmakeBuildType, doInstall):
   if doInstall:
      installCommand = 'cmake --build {0} --target install --config {0}'.format(cmakeBuildType)
      Process.run(installCommand)

def windows_cmake_and_build(
   cmakeGenerator, cmakeBuildType, staticLibraryName, cmakeDefinitions):
   CMake.generate('.', cmakeGenerator, cmakeBuildType, cmakeDefinitions, '.')
   cmakeBuildCommand = 'cmake --build . --config {0}'.format(cmakeBuildType)
   Process.run(cmakeBuildCommand)

def windows_runtests(cmakeBuildType, staticLibraryTestName):
   runTestsCommand = '{0}/{1}/{0}.exe'.format(staticLibraryTestName, cmakeBuildType)
   Process.run(runTestsCommand)

def windows_install(cmakeBuildType, doInstall):
   if doInstall:
      installCommand = 'cmake --build . --target install --config {0}'.format(cmakeBuildType)
      Process.run(installCommand)

if __name__ == "__main__": # pragma nocover
   main(sys.argv)
