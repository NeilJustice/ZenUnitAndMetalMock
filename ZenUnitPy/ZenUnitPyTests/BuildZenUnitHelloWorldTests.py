import platform
import os
import unittest
from unittest.mock import call, patch
from ZenUnitPy import ArgParser, UnitTester, BuildZenUnit, BuildZenUnitHelloWorld, Util, Process
import TestRandom

testNames = [
'main_ArgsLengthNot4_PrintsUsageAndExits1_test',
'main_ArgsLength4_CMakes_Builds_InstallsIfInstallDirectoryNotNoInstall_test'
]

class BuildZenUnitHelloWorldTests(unittest.TestCase):

   def setUp(self):
      self.cmakeGenerator = TestRandom.string()
      self.cmakeBuildType = TestRandom.string()
      self.cmakeDefinitions = TestRandom.string()

   def main_ArgsLengthNot4_PrintsUsageAndExits1_test(self):
      @patch('ZenUnitPy.Util.print_and_exit', spec_set=True)
      def testcase(argsLength, _1):
         invalidArgs = ['arg'] * argsLength
         #
         BuildZenUnitHelloWorld.main(invalidArgs)
         #
         Util.print_and_exit.assert_called_once_with(
'Invalid args: ' + ' '.join(invalidArgs) + '\n' +
"""Usage: python3 BuildZenUnitHelloWorld.py --generator=<CMakeGenerator> --buildType=<CMakeBuildType> --definitions=<QuotedSpaceSeparatedCMakeDefinitions>""", 1)
      testcase(0)
      testcase(3)
      testcase(5)

   def main_ArgsLength4_CMakes_Builds_InstallsIfInstallDirectoryNotNoInstall_test(self):
      @patch('ZenUnitPy.ArgParser.parse_arg', spec_set=True)
      @patch('platform.system', spec_set=True)
      @patch('ZenUnitPy.BuildZenUnit.linux_cmake_and_build', spec_set=True)
      @patch('ZenUnitPy.BuildZenUnit.linux_run_tests', spec_set=True)
      @patch('ZenUnitPy.BuildZenUnit.windows_cmake_and_build', spec_set=True)
      @patch('ZenUnitPy.Process.run', spec_set=True)
      @patch('os.chdir', spec_true=True)
      def testcase(platformSystem, expectLinux, _1, _2, _3, _4, _5, _6, _7):
         with self.subTest(f'{platformSystem}, {expectLinux}'):
            ArgParser.parse_arg.side_effect = [ self.cmakeGenerator, self.cmakeBuildType, self.cmakeDefinitions ]
            platform.system.return_value = platformSystem
            args = [ '.py', self.cmakeGenerator, self.cmakeBuildType, self.cmakeDefinitions ]
            #
            BuildZenUnitHelloWorld.main(args)
            #
            self.assertEqual(3, len(ArgParser.parse_arg.call_args_list))
            ArgParser.parse_arg.assert_has_calls([
               call('--generator', args[1]),
               call('--buildType', args[2]),
               call('--definitions', args[3])])
            platform.system.assert_called_once_with()
            if expectLinux:
               BuildZenUnit.linux_cmake_and_build.assert_called_once_with(
                  self.cmakeGenerator, self.cmakeBuildType, self.cmakeDefinitions)
               BuildZenUnit.linux_run_tests.assert_called_once_with('ZenUnitHelloWorldTests')
               os.chdir.assert_called_once_with('..')
            else:
               BuildZenUnit.windows_cmake_and_build.assert_called_once_with(
                  self.cmakeGenerator, self.cmakeBuildType, self.cmakeDefinitions)
               Process.run.assert_called_once_with(
                  rf'ZenUnitHelloWorld\StaticLibraryTests\{self.cmakeBuildType}\StaticLibraryTests.exe')
               os.chdir.assert_not_called()
      testcase('Linux', True)
      testcase('linux', True)
      testcase('Windows', False)
      testcase('OSX', False)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(BuildZenUnitHelloWorldTests, testNames)
