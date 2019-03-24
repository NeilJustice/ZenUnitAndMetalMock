import os
import platform
import sys
import unittest
from unittest.mock import call, patch
sys.path.append('..') # Jenkins
from ZenUnitPy import ArgParser, CMake, BuildZenUnitOrZenMock, Process, UnitTester, Util
import Random

testNames = [
'main_ArgsLengthNot4_PrintsUsageAndExits1_test',
'main_ArgsLength5_ZenUnitOrZenMockIsZenUnit_CMakes_Builds_RunsTestsIfLinuxOtherwisePostBuildStepRunsTestsOnWindows_test',
'main_ArgsLength5_ZenUnitOrZenMockIsZenMock_CMakes_Builds_RunsTestsIfLinuxOtherwisePostBuildStepRunsTestsOnWindows_test',
'linux_cmake_and_build_CMakes_BuildsWithNinja_test',
'windows_cmake_and_build_CMakes_BuildsWithMSBuild_test',
]

class BuildZenUnitTests(unittest.TestCase):

   def setUp(self):
      self.ZenUnitOrZenMock = Random.string()
      self.cmakeGenerator = Random.string()
      self.cmakeBuildType = Random.string()
      self.cmakeDefinitions = Random.string()

   def main_ArgsLengthNot4_PrintsUsageAndExits1_test(self):
      @patch('ZenUnitPy.Util.print_and_exit', spec_set=True)
      def testcase(argsLength, _1):
         with self.subTest(f'{argsLength}'):
            invalidArgs = [Random.string()] * argsLength
            #
            BuildZenUnitOrZenMock.main(invalidArgs)
            #
            Util.print_and_exit.assert_called_once_with(
'Invalid args: ' + ' '.join(invalidArgs) + '\n'
"""Usage: python3 BuildZenUnitOrZenMock.py --zenunit-or-zenmock=<ZenUnitOrZenMock> --cmake-generator=<CMakeGenerator> --cmake-build-type=<CMakeBuildType> --cmake-definitions=<QuotedSpaceSeparatedCMakeDefinitions>""", 1)
      testcase(0)
      testcase(1)
      testcase(2)
      testcase(3)
      testcase(4)
      testcase(6)

   def main_ArgsLength5_ZenUnitOrZenMockIsZenUnit_CMakes_Builds_RunsTestsIfLinuxOtherwisePostBuildStepRunsTestsOnWindows_test(self):
      @patch('platform.system', spec_set=True)
      @patch('ZenUnitPy.ArgParser.parse_arg', spec_set=True)
      @patch('ZenUnitPy.BuildZenUnitOrZenMock.linux_cmake_and_build', spec_set=True)
      @patch('ZenUnitPy.BuildZenUnitOrZenMock.windows_cmake_and_build', spec_set=True)
      @patch('ZenUnitPy.Process.run', spec_set=True)
      @patch('os.chdir', spec_true=True)
      def testcase(platformSystem, expectLinux, _1, _2, _3, _4, _5, _6):
         with self.subTest(f'{platformSystem}, {expectLinux}'):
            ArgParser.parse_arg.side_effect = ['ZenUnit', self.cmakeGenerator, self.cmakeBuildType, self.cmakeDefinitions]
            platform.system.return_value = platformSystem
            args = [Random.string(), Random.string(), Random.string(), Random.string(), Random.string()]
            #
            BuildZenUnitOrZenMock.main(args)
            #
            self.assertEqual(4, len(ArgParser.parse_arg.call_args_list))
            ArgParser.parse_arg.assert_has_calls([
               call('--zenunit-or-zenmock', args[1]),
               call('--cmake-generator', args[2]),
               call('--cmake-build-type', args[3]),
               call('--cmake-definitions', args[4])
            ])
            platform.system.assert_called_once_with()
            if expectLinux:
               BuildZenUnitOrZenMock.linux_cmake_and_build.assert_called_once_with(self.cmakeGenerator, self.cmakeBuildType, self.cmakeDefinitions)
               self.assertEqual(2, len(Process.run.call_args_list))
               Process.run.assert_has_calls([
                  call('ZenUnitLibraryTests/ZenUnitLibraryTests'),
                  call('ZenUnitUtilsAndAssertionTests/ZenUnitUtilsAndAssertionTests')])
               os.chdir.assert_called_once_with('..')
            else:
               BuildZenUnitOrZenMock.windows_cmake_and_build.assert_called_once_with(self.cmakeGenerator, self.cmakeBuildType, self.cmakeDefinitions)
               Process.run.assert_not_called()
               os.chdir.assert_not_called()
      testcase('Linux', True)
      testcase('linux', True)
      testcase('Windows', False)
      testcase('OSX', False)

   def main_ArgsLength5_ZenUnitOrZenMockIsZenMock_CMakes_Builds_RunsTestsIfLinuxOtherwisePostBuildStepRunsTestsOnWindows_test(self):
      @patch('platform.system', spec_set=True)
      @patch('ZenUnitPy.ArgParser.parse_arg', spec_set=True)
      @patch('ZenUnitPy.BuildZenUnitOrZenMock.linux_cmake_and_build', spec_set=True)
      @patch('ZenUnitPy.BuildZenUnitOrZenMock.windows_cmake_and_build', spec_set=True)
      @patch('ZenUnitPy.Process.run', spec_set=True)
      @patch('os.chdir', spec_true=True)
      def testcase(platformSystem, expectLinux, _1, _2, _3, _4, _5, _6):
         with self.subTest(f'{platformSystem}, {expectLinux}'):
            ArgParser.parse_arg.side_effect = ['ZenMock', self.cmakeGenerator, self.cmakeBuildType, self.cmakeDefinitions]
            platform.system.return_value = platformSystem
            args = [Random.string(), Random.string(), Random.string(), Random.string(), Random.string()]
            #
            BuildZenUnitOrZenMock.main(args)
            #
            self.assertEqual(4, len(ArgParser.parse_arg.call_args_list))
            ArgParser.parse_arg.assert_has_calls([
               call('--zenunit-or-zenmock', args[1]),
               call('--cmake-generator', args[2]),
               call('--cmake-build-type', args[3]),
               call('--cmake-definitions', args[4])
            ])
            platform.system.assert_called_once_with()
            if expectLinux:
               BuildZenUnitOrZenMock.linux_cmake_and_build.assert_called_once_with(self.cmakeGenerator, self.cmakeBuildType, self.cmakeDefinitions)
               Process.run.assert_called_once_with('ZenMockTests/ZenMockTests')
               os.chdir.assert_called_once_with('..')
            else:
               BuildZenUnitOrZenMock.windows_cmake_and_build.assert_called_once_with(self.cmakeGenerator, self.cmakeBuildType, self.cmakeDefinitions)
               Process.run.assert_not_called()
               os.chdir.assert_not_called()
      testcase('Linux', True)
      testcase('linux', True)
      testcase('Windows', False)
      testcase('OSX', False)

   def linux_cmake_and_build_CMakes_BuildsWithNinja_test(self):
      @patch('ZenUnitPy.CMake.generate', spec_set=True)
      @patch('ZenUnitPy.Process.run', spec_set=True)
      def testcase(cmakeDefinitions, expectedCMakeDefinitionsArgument, _1, _2):
         with self.subTest(f'{cmakeDefinitions, expectedCMakeDefinitionsArgument}'):
            #
            BuildZenUnitOrZenMock.linux_cmake_and_build(self.cmakeGenerator, self.cmakeBuildType, cmakeDefinitions)
            #
            CMake.generate.assert_called_once_with(
               self.cmakeBuildType, self.cmakeGenerator, self.cmakeBuildType, expectedCMakeDefinitionsArgument, '..')
            Process.run.assert_called_once_with('ninja -v')
      testcase('', '')
      testcase('-DSanitizerMode=ON', '-DSanitizerMode=ON')
      testcase('-DOption=ON', '-DOption=ON')

   def windows_cmake_and_build_CMakes_BuildsWithMSBuild_test(self):
      @patch('ZenUnitPy.CMake.generate', spec_set=True)
      @patch('ZenUnitPy.Process.run', spec_set=True)
      def testcase(cmakeDefinitions, expectedCMakeDefinitionsArgument, _1, _2):
         with self.subTest(f'{cmakeDefinitions, expectedCMakeDefinitionsArgument, }'):
            #
            BuildZenUnitOrZenMock.windows_cmake_and_build(self.cmakeGenerator, self.cmakeBuildType, cmakeDefinitions)
            #
            CMake.generate.assert_called_once_with('.', self.cmakeGenerator, self.cmakeBuildType, expectedCMakeDefinitionsArgument, '.')
            expectedCMakeBuildCommand = 'cmake --build . --config {0}'.format(self.cmakeBuildType)
            Process.run.assert_called_once_with(expectedCMakeBuildCommand)
      testcase('', '')
      testcase('-DSanitizerMode=ON', '-DSanitizerMode=ON')
      testcase('-DOption=ON', '-DOption=ON')

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(BuildZenUnitTests, testNames)
