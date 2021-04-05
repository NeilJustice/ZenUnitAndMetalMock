import os
import platform
import unittest
from unittest.mock import call, patch
from ZenUnitPy import ArgParser, CMake, BuildZenUnitAndMetalMock, Process, Random, UnitTester, Util

testNames = [
'main_ArgsLengthIsNot4_PrintsUsageAndExits1_test',
'main_ArgsLengthIs4_CMakes_Builds_Returns0_test',
'linux_cmake_and_build_RunsCMakes_RunsNinja_test',
'windows_cmake_build_RunsCMakes_RunsCMakeBuildToRunMSBuild_test',
]

class BuildZenUnitTests(unittest.TestCase):

   def setUp(self):
      self.cmakeGenerator = Random.string()
      self.cmakeBuildType = Random.string()
      self.cmakeDefinitions = Random.string()

   def main_ArgsLengthIsNot4_PrintsUsageAndExits1_test(self):
      @patch('ZenUnitPy.Util.print_and_exit', spec_set=True)
      def testcase(argsLength, _1):
         with self.subTest(f'{argsLength}'):
            invalidArgs = [Random.string()] * argsLength
            #
            BuildZenUnitAndMetalMock.main(invalidArgs)
            #
            Util.print_and_exit.assert_called_once_with(
'Invalid args: ' + ' '.join(invalidArgs) + '\n'
"""Usage: python BuildZenUnitAndMetalMock.py --cmake-generator=<CMakeGenerator> --cmake-build-type=<CMakeBuildType> --cmake-definitions=<QuotedSpaceSeparatedCMakeDefinitions>""", 1)
      testcase(0)
      testcase(1)
      testcase(2)
      testcase(3)
      testcase(5)

   def main_ArgsLengthIs4_CMakes_Builds_Returns0_test(self):
      @patch('platform.system', spec_set=True)
      @patch('ZenUnitPy.ArgParser.parse_arg', spec_set=True)
      @patch('ZenUnitPy.BuildZenUnitAndMetalMock.linux_cmake_build', spec_set=True)
      @patch('ZenUnitPy.BuildZenUnitAndMetalMock.windows_cmake_build', spec_set=True)
      @patch('ZenUnitPy.Process.fail_fast_run', spec_set=True)
      @patch('os.chdir', spec_true=True)
      def testcase(platformSystem, expectLinux, _1, _2, _3, _4, _5, _6):
         with self.subTest(f'{platformSystem}, {expectLinux}'):
            ArgParser.parse_arg.side_effect = [self.cmakeGenerator, self.cmakeBuildType, self.cmakeDefinitions]
            platform.system.return_value = platformSystem
            args = [Random.string(), Random.string(), Random.string(), Random.string()]
            #
            exitCode = BuildZenUnitAndMetalMock.main(args)
            #
            self.assertEqual(3, len(ArgParser.parse_arg.call_args_list))
            ArgParser.parse_arg.assert_has_calls([
               call('--cmake-generator', args[1]),
               call('--cmake-build-type', args[2]),
               call('--cmake-definitions', args[3])
            ])
            platform.system.assert_called_once_with()
            if expectLinux:
               BuildZenUnitAndMetalMock.linux_cmake_build.assert_called_once_with(self.cmakeGenerator, self.cmakeBuildType, self.cmakeDefinitions)
               self.assertEqual(6, len(Process.fail_fast_run.call_args_list))
               Process.fail_fast_run.assert_has_calls([
                  call('MetalMockExamples/MetalMockExamples --test-runs=2 --random'),
                  call('MetalMockTests/MetalMockTests --test-runs=2 --random'),
                  call('ZenUnitCompileSpeedTests/ZenUnitCompileSpeedTests --test-runs=2 --random'),
                  call('ZenUnitExamples/ZenUnitExamples --test-runs=2 --random'),
                  call('ZenUnitLibraryTests/ZenUnitLibraryTests --test-runs=2 --random'),
                  call('ZenUnitUtilsAndAssertionTests/ZenUnitUtilsAndAssertionTests --test-runs=2 --random')])
               os.chdir.assert_called_once_with('..')
            else:
               BuildZenUnitAndMetalMock.windows_cmake_build.assert_called_once_with(self.cmakeGenerator, self.cmakeBuildType, self.cmakeDefinitions)
               Process.fail_fast_run.assert_has_calls([
                  call(f'MetalMockExamples/{self.cmakeBuildType}/MetalMockExamples.exe --random'),
                  call(f'MetalMockTests/{self.cmakeBuildType}/MetalMockTests.exe --random'),
                  call(f'ZenUnitCompileSpeedTests/{self.cmakeBuildType}/ZenUnitCompileSpeedTests.exe --random'),
                  call(f'ZenUnitExamples/{self.cmakeBuildType}/ZenUnitExamples.exe --random'),
                  call(f'ZenUnitLibraryTests/{self.cmakeBuildType}/ZenUnitLibraryTests.exe --random'),
                  call(f'ZenUnitUtilsAndAssertionTests/{self.cmakeBuildType}/ZenUnitUtilsAndAssertionTests.exe --random')])
               os.chdir.assert_not_called()
            self.assertEqual(0, exitCode)
      testcase('Linux', True)
      testcase('linux', True)
      testcase('Windows', False)
      testcase('OSX', False)

   def linux_cmake_and_build_RunsCMakes_RunsNinja_test(self):
      @patch('ZenUnitPy.CMake.generate', spec_set=True)
      @patch('ZenUnitPy.Process.fail_fast_run', spec_set=True)
      def testcase(cmakeDefinitions, expectedCMakeDefinitionsArgument, _1, _2):
         with self.subTest(f'{cmakeDefinitions, expectedCMakeDefinitionsArgument}'):
            #
            BuildZenUnitAndMetalMock.linux_cmake_build(self.cmakeGenerator, self.cmakeBuildType, cmakeDefinitions)
            #
            CMake.generate.assert_called_once_with(self.cmakeBuildType, self.cmakeGenerator, self.cmakeBuildType, expectedCMakeDefinitionsArgument, '..')
            Process.fail_fast_run.assert_called_once_with('ninja -v')
      testcase('', '')
      testcase('-DOptionA=ON', '-DOptionA=ON')
      testcase('-DOptionB=ON', '-DOptionB=ON')

   def windows_cmake_build_RunsCMakes_RunsCMakeBuildToRunMSBuild_test(self):
      @patch('ZenUnitPy.CMake.generate', spec_set=True)
      @patch('ZenUnitPy.Process.fail_fast_run', spec_set=True)
      def testcase(cmakeDefinitions, expectedCMakeDefinitionsArgument, _1, _2):
         with self.subTest(f'{cmakeDefinitions, expectedCMakeDefinitionsArgument, }'):
            #
            BuildZenUnitAndMetalMock.windows_cmake_build(self.cmakeGenerator, self.cmakeBuildType, cmakeDefinitions)
            #
            CMake.generate.assert_called_once_with('.', self.cmakeGenerator, self.cmakeBuildType, expectedCMakeDefinitionsArgument, '.')
            expectedCMakeBuildCommand = 'cmake.exe --build . --config {0}'.format(self.cmakeBuildType)
            Process.fail_fast_run.assert_called_once_with(expectedCMakeBuildCommand)
      testcase('', '')
      testcase('-DOptionA=ON', '-DOptionA=ON')
      testcase('-DOptionB=ON', '-DOptionB=ON')

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(BuildZenUnitTests, testNames)
