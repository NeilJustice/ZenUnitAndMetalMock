import os
import platform
import sys
import unittest
from unittest.mock import call, patch
sys.path.append('..') # Jenkins
from ZenUnitPy import ArgParser, CMake, BuildZenUnit, Process, UnitTester, Util
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

class BuildZenUnitTests(unittest.TestCase):

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
            BuildZenUnit.main(invalidArgs)
            #
            Util.print_and_exit.assert_called_once_with(
'Invalid args: ' + ' '.join(invalidArgs) + '\n' +
"""Usage: python3 BuildZenUnit.py --generator=<CMakeGenerator> --buildType=<CMakeBuildType> --definitions=<QuotedSpaceSeparatedCMakeDefinitions> --installDirectory=<DirectoryOrNoInstall>""", 1)
      testcase(0)
      testcase(4)
      testcase(6)

   def main_ArgsLength5_CMakes_Builds_InstallsIfInstallDirectoryNotNoInstall_test(self):
      @patch('platform.system', spec_set=True)
      @patch('ZenUnitPy.ArgParser.parse_arg', spec_set=True)
      @patch('ZenUnitPy.BuildZenUnit.linux_cmake_and_build', spec_set=True)
      @patch('ZenUnitPy.BuildZenUnit.linux_run_zenunit_tests', spec_set=True)
      @patch('ZenUnitPy.BuildZenUnit.windows_cmake_and_build', spec_set=True)
      @patch('ZenUnitPy.BuildZenUnit.windows_run_zenunit_tests', spec_set=True)
      @patch('ZenUnitPy.BuildZenUnit.optionally_install', spec_true=True)
      @patch('os.chdir', spec_true=True)
      def testcase(platformSystem, expectLinux, _1, _2, _3, _4, _5, _6, _7, _8):
         with self.subTest(f'{platformSystem}, {expectLinux}'):
            ArgParser.parse_arg.side_effect = [ self.generator, self.buildType, self.definitions, self.installDirectory ]
            platform.system.return_value = platformSystem
            args = [ '.py', self.generator, self.buildType, self.definitions, self.installDirectory ]
            #
            BuildZenUnit.main(args)
            #
            self.assertEqual(4, len(ArgParser.parse_arg.call_args_list))
            ArgParser.parse_arg.assert_has_calls([
               call('--generator', args[1]),
               call('--buildType', args[2]),
               call('--definitions', args[3]),
               call('--installDirectory', args[4])
            ])
            platform.system.assert_called_once_with()
            if expectLinux:
               BuildZenUnit.linux_cmake_and_build.assert_called_once_with(self.generator, self.buildType, self.definitions)
               BuildZenUnit.linux_run_zenunit_tests.assert_called_once_with('ZenUnitTests')
               BuildZenUnit.optionally_install.assert_called_once_with(self.buildType, self.installDirectory)
               os.chdir.assert_called_once_with('..')
            else:
               BuildZenUnit.windows_cmake_and_build.assert_called_once_with(self.generator, self.buildType, self.definitions)
               BuildZenUnit.windows_run_zenunit_tests.assert_called_once_with(self.buildType, 'ZenUnitTests')
               BuildZenUnit.optionally_install.assert_called_once_with(self.buildType, self.installDirectory)
               os.chdir.assert_not_called()
      testcase('Linux', True)
      testcase('linux', True)
      testcase('Windows', False)
      testcase('OSX', False)

   @patch('ZenUnitPy.CMake.generate', spec_set=True)
   @patch('ZenUnitPy.Process.run', spec_set=True)
   def linux_cmake_and_build_CMakes_BuildsWithNinja_test(self, _1, _2):
      #
      BuildZenUnit.linux_cmake_and_build(self.generator, self.buildType, self.definitions)
      #
      CMake.generate.assert_called_once_with(self.buildType, self.generator, self.buildType, self.definitions, '..')
      Process.run.assert_called_once_with('ninja -v')

   @patch('ZenUnitPy.Process.run', spec_set=True)
   def linux_run_zenunit_tests_RunsTestExe_test(self, _1):
      testsProjectName = TestRandom.string()
      #
      BuildZenUnit.linux_run_zenunit_tests(testsProjectName)
      #
      Process.run.assert_called_once_with(f'{testsProjectName}/{testsProjectName}')

   def optionally_install_RunsCMakeInstallTarget_test(self):
      @patch('ZenUnitPy.Process.run', spec_true=True)
      def testcase(installDirectory, expectCallToCMakeInstall, _1):
         with self.subTest(f'{installDirectory}, {expectCallToCMakeInstall}'):
            #
            BuildZenUnit.optionally_install(self.buildType, installDirectory)
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
      BuildZenUnit.windows_cmake_and_build(self.generator, self.buildType, self.definitions)
      #
      CMake.generate.assert_called_once_with('.', self.generator, self.buildType, self.definitions, '.')
      expectedCMakeBuildCommand = 'cmake --build . --config {0}'.format(self.buildType)
      Process.run.assert_called_once_with(expectedCMakeBuildCommand)

   @patch('ZenUnitPy.Process.run', spec_set=True)
   def windows_run_zenunit_tests_RunsTestExe_test(self, _1):
      testsProjectName = TestRandom.string()
      #
      BuildZenUnit.windows_run_zenunit_tests(self.buildType, testsProjectName)
      #
      expectedRunTestsCommand = f'{testsProjectName}/{self.buildType}/{testsProjectName}.exe'
      Process.run.assert_called_once_with(expectedRunTestsCommand)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(BuildZenUnitTests, testNames)
