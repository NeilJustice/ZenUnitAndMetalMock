import os
import platform
import sys
import unittest
from unittest.mock import patch
sys.path.append('..') # Jenkins
from ZenUnitPy import CMake, CMakeBuildZenUnit, Process, UnitTester, Util
import TestRandom

testNames = [
'main_ArgsLengthNot5_PrintsUsageAndExits1_test',
'main_ArgsLength5_CMakes_Builds_InstallsIfInstallDirectoryNotNoInstall_test',
'linux_cmake_and_build_CMakes_BuildsWithNinja_test',
'linux_run_zenunit_tests_RunsTestExe_test',
'optionally_install_RunsCMakeInstallTarget_test',
'windows_cmake_and_build_CMakes_BuildsWithMSBuild_test',
'windows_run_zenunit_tests_RunsTestExe_test'
]

class CMakeBuildZenUnitTests(unittest.TestCase):

   def setUp(self):
      self.generator = TestRandom.string()
      self.buildType = TestRandom.string()
      self.definitions = TestRandom.string()
      self.installDirectory = TestRandom.string()

   def main_ArgsLengthNot5_PrintsUsageAndExits1_test(self):
      @patch('ZenUnitPy.Util.print_and_exit', spec_set=True)
      def testcase(argsLength, _1):
         with self.subTest(f'{argsLength}'):
            invalidArgs = ['arg'] * argsLength
            #
            CMakeBuildZenUnit.main(invalidArgs)
            #
            Util.print_and_exit.assert_called_once_with(
'Invalid args: ' + ' '.join(invalidArgs) + '\n' +
"""Usage: python3 CMakeBuildZenUnit.py --generator=<CMakeGenerator> --buildType=<CMakeBuildType> --definitions=<QuotedSpaceSeparatedCMakeDefinitions> --installDirectory=<DirectoryOrNoInstall>""", 1)
      testcase(0)
      testcase(4)
      testcase(6)

   def main_ArgsLength5_CMakes_Builds_InstallsIfInstallDirectoryNotNoInstall_test(self):
      @patch('platform.system', spec_set=True)
      @patch('ZenUnitPy.CMakeBuildZenUnit.linux_cmake_and_build', spec_set=True)
      @patch('ZenUnitPy.CMakeBuildZenUnit.linux_run_zenunit_tests', spec_set=True)
      @patch('ZenUnitPy.CMakeBuildZenUnit.windows_cmake_and_build', spec_set=True)
      @patch('ZenUnitPy.CMakeBuildZenUnit.windows_run_zenunit_tests', spec_set=True)
      @patch('ZenUnitPy.CMakeBuildZenUnit.optionally_install', spec_true=True)
      @patch('os.chdir', spec_true=True)
      def testcase(platformSystem, expectLinux, _1, _2, _3, _4, _5, _6, _7):
         with self.subTest(f'{platformSystem}, {expectLinux}'):
            platform.system.return_value = platformSystem
            args = [ '.py', self.generator, self.buildType, self.definitions, self.installDirectory ]
            #
            CMakeBuildZenUnit.main(args)
            #
            platform.system.assert_called_once_with()
            if expectLinux:
               CMakeBuildZenUnit.linux_cmake_and_build.assert_called_once_with(self.generator, self.buildType, self.definitions)
               CMakeBuildZenUnit.linux_run_zenunit_tests.assert_called_once_with('ZenUnitTests')
               CMakeBuildZenUnit.optionally_install.assert_called_once_with(self.buildType, self.installDirectory)
               os.chdir.assert_called_once_with('..')
            else:
               CMakeBuildZenUnit.windows_cmake_and_build.assert_called_once_with(self.generator, self.buildType, self.definitions)
               CMakeBuildZenUnit.windows_run_zenunit_tests.assert_called_once_with(self.buildType, 'ZenUnitTests')
               CMakeBuildZenUnit.optionally_install.assert_called_once_with(self.buildType, self.installDirectory)
               os.chdir.assert_not_called()
      testcase('Linux', True)
      testcase('linux', True)
      testcase('Windows', False)
      testcase('OSX', False)

   @patch('ZenUnitPy.CMake.generate', spec_set=True)
   @patch('ZenUnitPy.Process.run', spec_set=True)
   def linux_cmake_and_build_CMakes_BuildsWithNinja_test(self, _1, _2):
      #
      CMakeBuildZenUnit.linux_cmake_and_build(self.generator, self.buildType, self.definitions)
      #
      CMake.generate.assert_called_once_with(self.buildType, self.generator, self.buildType, self.definitions, '..')
      Process.run.assert_called_once_with('ninja -v')

   @patch('ZenUnitPy.Process.run', spec_set=True)
   def linux_run_zenunit_tests_RunsTestExe_test(self, _1):
      testsProjectName = TestRandom.string()
      #
      CMakeBuildZenUnit.linux_run_zenunit_tests(testsProjectName)
      #
      Process.run.assert_called_once_with(f'{testsProjectName}/{testsProjectName}')

   def optionally_install_RunsCMakeInstallTarget_test(self):
      @patch('ZenUnitPy.Process.run', spec_true=True)
      def testcase(installDirectory, expectCallToCMakeInstall, _1):
         with self.subTest(f'{installDirectory}, {expectCallToCMakeInstall}'):
            #
            CMakeBuildZenUnit.optionally_install(self.buildType, installDirectory)
            #
            if expectCallToCMakeInstall:
               expectedInstallCommand = 'cmake --build . --target install --config {0}'.format(self.buildType)
               Process.run.assert_called_once_with(expectedInstallCommand)
            else:
               Process.run.assert_not_called()
      testcase('/usr/local', True)
      testcase('~/install', True)
      testcase('NoInstall', False)
      testcase('noinstall', False)

   @patch('ZenUnitPy.CMake.generate', spec_set=True)
   @patch('ZenUnitPy.Process.run', spec_set=True)
   def windows_cmake_and_build_CMakes_BuildsWithMSBuild_test(self, _1, _2):
      #
      CMakeBuildZenUnit.windows_cmake_and_build(self.generator, self.buildType, self.definitions)
      #
      CMake.generate.assert_called_once_with('.', self.generator, self.buildType, self.definitions, '.')
      expectedCMakeBuildCommand = 'cmake --build . --config {0}'.format(self.buildType)
      Process.run.assert_called_once_with(expectedCMakeBuildCommand)

   @patch('ZenUnitPy.Process.run', spec_set=True)
   def windows_run_zenunit_tests_RunsTestExe_test(self, _1):
      testsProjectName = TestRandom.string()
      #
      CMakeBuildZenUnit.windows_run_zenunit_tests(self.buildType, testsProjectName)
      #
      expectedRunTestsCommand = f'{testsProjectName}/{self.buildType}/{testsProjectName}.exe'
      Process.run.assert_called_once_with(expectedRunTestsCommand)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(CMakeBuildZenUnitTests, testNames)
