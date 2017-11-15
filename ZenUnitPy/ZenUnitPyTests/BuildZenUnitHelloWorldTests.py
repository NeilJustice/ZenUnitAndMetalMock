import platform
import os
import unittest
from unittest.mock import call, patch
from ZenUnitPy import ArgParser, UnitTester, BuildZenUnit, BuildZenUnitHelloWorld, Util, Process
import Random

testNames = [
'main_ArgsLengthNot4_PrintsUsageAndExits1_test',
'main_ArgsLength4_CMakes_Builds_InstallsIfInstallDirectoryNotNoInstall_test'
]

class BuildZenUnitHelloWorldTests(unittest.TestCase):

   def setUp(self):
      self.cmakeGenerator = Random.string()
      self.cmakeBuildType = Random.string()
      self.cmakeDefinitions = Random.string()

   def main_ArgsLengthNot4_PrintsUsageAndExits1_test(self):
      @patch('ZenUnitPy.Util.print_and_exit', spec_set=True)
      def testcase(argsLength, _1):
         with self.subTest(f'{argsLength}'):
            invalidArgs = [Random.string()] * argsLength
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
      @patch('ZenUnitPy.BuildZenUnit.windows_cmake_and_build', spec_set=True)
      @patch('ZenUnitPy.Process.run', spec_set=True)
      @patch('os.chdir', spec_true=True)
      def testcase(platformSystem, expectLinux, _1, _2, _3, _4, _5, _6):
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
            os.chdir.assert_called_with('ZenUnitHelloWorld')
            platform.system.assert_called_once_with()
            if expectLinux:
               BuildZenUnit.linux_cmake_and_build.assert_called_once_with(
                  self.cmakeGenerator, self.cmakeBuildType, self.cmakeDefinitions, 'noinstall')
               Process.run.assert_called_once_with('StaticLibraryTests/StaticLibraryTests')
            else:
               os.chdir.assert_called_once_with('ZenUnitHelloWorld')
               BuildZenUnit.windows_cmake_and_build.assert_called_once_with(
                  self.cmakeGenerator, self.cmakeBuildType, self.cmakeDefinitions, 'noinstall')
               Process.run.assert_called_once_with(
                  rf'StaticLibraryTests\{self.cmakeBuildType}\StaticLibraryTests.exe')
      testcase('Linux', True)
      testcase('linux', True)
      testcase('Windows', False)
      testcase('OSX', False)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(BuildZenUnitHelloWorldTests, testNames)
