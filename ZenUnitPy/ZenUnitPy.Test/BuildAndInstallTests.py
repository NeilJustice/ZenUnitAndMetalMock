import os
import platform
import sys
import unittest
from unittest.mock import patch
sys.path.append('..') # Jenkins
from ZenUnitPy import CMake, BuildAndInstall, Process, UnitTester, Util

testNames = [
'main_ArgsLengthNot8_PrintsUsageAndExits1_test',
'main_ArgsLength8_CallsCMakeAndBuild_CallsRunTestsAndInstall_test',
'linux_cmake_and_build_CMakes_BuildsWithNinja_test',
'linux_check_comment_section_test',
'linux_runtests_RunsTestExe_test',
'linux_install_RunsCMakeInstallTarget_test',
'windows_cmake_and_build_CMakes_BuildsWithMSBuild_test',
'windows_runtests_RunsTestExe_test',
'windows_install_RunsCMakeInstallTarget_test'
]

class BuildAndInstallTests(unittest.TestCase):

   CMakeGenerator = 'CMakeGenerator'
   CMakeBuildType = 'CMakeBuildType'
   StaticLibraryName = 'StaticLibraryName'
   StaticLibraryTestName = 'StaticLibraryTestName'
   ExpectedCommentSectionSubstring = 'ExpectedCommentSectionSubstring'
   CMakeDefinitions = 'CMakeDefinitions'

   def main_ArgsLengthNot8_PrintsUsageAndExits1_test(self):
      @patch('ZenUnitPy.Util.print_and_exit', spec_set=True)
      def testcase(argsLength, _1):
         invalidArgs = ['arg'] * argsLength
         #
         BuildAndInstall.main(invalidArgs)
         #
         Util.print_and_exit.assert_called_once_with(
'Invalid args: ' + ' '.join(invalidArgs) + '\n' +
"""Usage: python3 CMakeBuildRunTestsInstall.py
<CMakeGenerator>
<CMakeBuildType>
<StaticLibraryName>
<StaticLibraryTestName>
<ExpectedCommentSectionSubstring>
<CMakeDefinitions>
<Install|NoInstall>""", 1)
      testcase(0)
      testcase(7)
      testcase(9)

   def main_ArgsLength8_CallsCMakeAndBuild_CallsRunTestsAndInstall_test(self):
      @patch('platform.system', spec_set=True)
      @patch('ZenUnitPy.BuildAndInstall.linux_cmake_and_build', spec_set=True)
      @patch('ZenUnitPy.BuildAndInstall.linux_check_comment_section', spec_set=True)
      @patch('ZenUnitPy.BuildAndInstall.linux_runtests', spec_set=True)
      @patch('ZenUnitPy.BuildAndInstall.linux_install', spec_set=True)
      @patch('ZenUnitPy.BuildAndInstall.windows_cmake_and_build', spec_set=True)
      @patch('ZenUnitPy.BuildAndInstall.windows_runtests', spec_set=True)
      @patch('ZenUnitPy.BuildAndInstall.windows_install', spec_true=True)
      def testcase(
         platformSystem, expectLinux, installNoInstallString, expectInstall,
         _1, _2, _3, _4, _5, _6, _7, _8):
         platform.system.return_value = platformSystem
         Args = [
            '.py',
            self.CMakeGenerator,
            self.CMakeBuildType,
            self.StaticLibraryName,
            self.StaticLibraryTestName,
            self.ExpectedCommentSectionSubstring,
            self.CMakeDefinitions,
            installNoInstallString ]
         #
         BuildAndInstall.main(Args)
         #
         platform.system.assert_called_once_with()
         if expectLinux:
            BuildAndInstall.linux_cmake_and_build.assert_called_once_with(
               self.CMakeGenerator, self.CMakeBuildType,
               self.StaticLibraryName, self.CMakeDefinitions)
            BuildAndInstall.linux_runtests.\
               assert_called_once_with(self.CMakeBuildType, self.StaticLibraryTestName)
            BuildAndInstall.linux_install.\
               assert_called_once_with(self.CMakeBuildType, expectInstall)
            BuildAndInstall.linux_check_comment_section.assert_called_once_with(
               self.CMakeBuildType, self.StaticLibraryName, self.ExpectedCommentSectionSubstring)
         else:
            BuildAndInstall.windows_cmake_and_build.assert_called_once_with(
               self.CMakeGenerator, self.CMakeBuildType,
               self.StaticLibraryName, self.CMakeDefinitions)
            BuildAndInstall.windows_runtests.\
               assert_called_once_with(self.CMakeBuildType, self.StaticLibraryTestName)
            BuildAndInstall.windows_install.\
               assert_called_once_with(self.CMakeBuildType, expectInstall)
      testcase('Linux', True, 'Install', True)
      testcase('Linux', True, 'install', False)
      testcase('Linux', True, 'NoInstall', False)
      testcase('Linux', True, 'noinstall', False)
      testcase('linux', False, 'Install', True)
      testcase('Windows', False, 'Install', True)
      testcase('windows', False, 'Install', True)
      testcase('Neither', False, 'Install', True)

   @patch('ZenUnitPy.CMake.generate', spec_set=True)
   @patch('ZenUnitPy.Process.run', spec_set=True)
   @patch('os.chdir', spec_set=True)
   def linux_cmake_and_build_CMakes_BuildsWithNinja_test(self, _1, _2, _3):
      #
      BuildAndInstall.linux_cmake_and_build(
         self.CMakeGenerator, self.CMakeBuildType, self.StaticLibraryName, self.CMakeDefinitions)
      #
      CMake.generate.assert_called_once_with(
         self.CMakeBuildType, self.CMakeGenerator, self.CMakeBuildType,
         self.CMakeDefinitions, '..')
      Process.run.assert_called_once_with('ninja -v')
      os.chdir.assert_called_once_with('..')

   def linux_check_comment_section_test(self):
      @patch('ZenUnitPy.Process.run_and_check_stdout_for_substring', spec_set=True)
      def testcase(expectedCommentSectionSubstring, expectReadElfProcessRun, _1):
         #
         BuildAndInstall.linux_check_comment_section(
            self.CMakeBuildType, self.StaticLibraryName, expectedCommentSectionSubstring)
         #
         if expectReadElfProcessRun:
            expectedreadelfCommand = 'readelf -p .comment {0}/{1}/lib{1}{0}.a'.\
               format(self.CMakeBuildType, self.StaticLibraryName)
            Process.run_and_check_stdout_for_substring.assert_called_once_with(
               expectedreadelfCommand, expectedCommentSectionSubstring)
         else:
            Process.run_and_check_stdout_for_substring.assert_not_called()
      testcase("", False)
      testcase("clang version", True)
      testcase("GCC:", True)

   @patch('ZenUnitPy.Process.run', spec_set=True)
   def linux_runtests_RunsTestExe_test(self, _1):
      #
      BuildAndInstall.linux_runtests(self.CMakeBuildType, self.StaticLibraryTestName)
      #
      expectedRunTestsCommand = '{0}/{1}/{1}'.format(self.CMakeBuildType, self.StaticLibraryTestName)
      Process.run.assert_called_once_with(expectedRunTestsCommand)

   def linux_install_RunsCMakeInstallTarget_test(self):
      @patch('ZenUnitPy.Process.run', spec_true=True)
      def testcase(doInstall, expectedRunInstallCommand, _1):
         #
         BuildAndInstall.linux_install(self.CMakeBuildType, doInstall)
         #
         if expectedRunInstallCommand:
            expectedInstallCommand =\
               'cmake --build {0} --target install --config {0}'.format(self.CMakeBuildType)
            Process.run.assert_called_once_with(expectedInstallCommand)
         else:
            Process.run.assert_not_called()
      testcase(True, True)
      testcase(False, False)

   @patch('ZenUnitPy.CMake.generate', spec_set=True)
   @patch('ZenUnitPy.Process.run', spec_set=True)
   def windows_cmake_and_build_CMakes_BuildsWithMSBuild_test(self, _1, _2):
      #
      BuildAndInstall.windows_cmake_and_build(
         self.CMakeGenerator, self.CMakeBuildType, self.StaticLibraryName, self.CMakeDefinitions)
      #
      CMake.generate.assert_called_once_with(
         '.', self.CMakeGenerator, self.CMakeBuildType, self.CMakeDefinitions, '.')
      expectedMSBuildCommand = 'MSBuild {0}.sln /p:Configuration={1} /m'.\
         format(self.StaticLibraryName, self.CMakeBuildType)
      Process.run.assert_called_once_with(expectedMSBuildCommand)

   @patch('ZenUnitPy.Process.run', spec_set=True)
   def windows_runtests_RunsTestExe_test(self, _1):
      #
      BuildAndInstall.windows_runtests(self.CMakeBuildType, self.StaticLibraryTestName)
      #
      expectedRunTestsCommand = '{0}/{1}/{0}.exe'.format(self.StaticLibraryTestName, self.CMakeBuildType)
      Process.run.assert_called_once_with(expectedRunTestsCommand)

   def windows_install_RunsCMakeInstallTarget_test(self):
      @patch('ZenUnitPy.Process.run', spec_true=True)
      def testcase(doInstall, expectedRunInstallCommand, _1):
         #
         BuildAndInstall.windows_install(self.CMakeBuildType, doInstall)
         #
         if expectedRunInstallCommand:
            expectedInstallCommand =\
               'cmake --build . --target install --config {0}'.format(self.CMakeBuildType)
            Process.run.assert_called_once_with(expectedInstallCommand)
         else:
            Process.run.assert_not_called()
      testcase(True, True)
      testcase(False, False)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(BuildAndInstallTests, testNames)
