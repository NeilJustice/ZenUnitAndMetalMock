import os
import platform
import sys
import unittest
from unittest.mock import call, patch
import docopt # type: ignore
from ZenUnitDevOpsPython import CMake, BuildAndTestZenUnitAndMetalMock, Process
from ZenUnitDevOpsPythonTests import Random, UnitTester

testNames = [
'test_docstring__IsExpectedString',
'test_main_CMakesZenUnitAndMetalMock_BuildsZenUnitAndMetalMock_RunsAllUnitTestBinaries_Returns0',
'test_linux_cmake_and_build_RunsCMakes_RunsNinja',
'test_windows_cmake_build_RunsCMakes_RunsCMakeBuildToRunMSBuild',
]

class BuildZenUnitTests(unittest.TestCase):

   def setUp(self):
      self.cmakeBuildType = Random.string()
      self.cmakeDefinitions = Random.string()

   def test_docstring__IsExpectedString(self):
      self.assertEqual("""Usage: BuildAndTestZenUnitAndMetalMock.py --cmake-build-type=<CMakeBuildType> --cmake-definitions=<QuotedSpaceSeparatedCMakeDefinitions>""", BuildAndTestZenUnitAndMetalMock.__doc__)

   def test_main_CMakesZenUnitAndMetalMock_BuildsZenUnitAndMetalMock_RunsAllUnitTestBinaries_Returns0(self):
      @patch('docopt.docopt', spec_set=True)
      @patch('platform.system', spec_set=True)
      @patch('ZenUnitDevOpsPython.BuildAndTestZenUnitAndMetalMock.linux_cmake_build', spec_set=True)
      @patch('ZenUnitDevOpsPython.BuildAndTestZenUnitAndMetalMock.windows_cmake_build', spec_set=True)
      @patch('ZenUnitDevOpsPython.Process.fail_fast_run', spec_set=True)
      @patch('os.chdir', spec_true=True)
      @patch('builtins.print', spec_set=True)
      def testcase(platformSystem, expectLinux, printMock, _1, _2, _3, _4, _5, _6):
         with self.subTest(f'{platformSystem}, {expectLinux}'):
            docopt.docopt.return_value =\
            {
               '--cmake-build-type': self.cmakeBuildType,
               '--cmake-definitions': self.cmakeDefinitions
            }
            platform.system.return_value = platformSystem
            #
            exitCode = BuildAndTestZenUnitAndMetalMock.main()
            #
            expectedRunningSysArgvMessage = f'Running {sys.argv}\n'
            printMock.assert_called_once_with(expectedRunningSysArgvMessage)
            docopt.docopt.assert_called_once_with(BuildAndTestZenUnitAndMetalMock.__doc__)
            platform.system.assert_called_once_with()
            if expectLinux:
               BuildAndTestZenUnitAndMetalMock.linux_cmake_build.assert_called_once_with(self.cmakeBuildType, self.cmakeDefinitions)
               self.assertEqual(6, len(Process.fail_fast_run.call_args_list))
               Process.fail_fast_run.assert_has_calls([
                  call('MetalMockExamples/MetalMockExamples --test-runs=2 --random --max-test-milliseconds=200'),
                  call('MetalMockTests/MetalMockTests --test-runs=2 --random --max-test-milliseconds=200'),
                  call('ZenUnitCompileSpeedTests/ZenUnitCompileSpeedTests --test-runs=2 --random --max-test-milliseconds=200'),
                  call('ZenUnitExamples/ZenUnitExamples --test-runs=2 --random --max-test-milliseconds=200'),
                  call('ZenUnitLibraryTests/ZenUnitLibraryTests --test-runs=2 --random --max-test-milliseconds=200'),
                  call('ZenUnitUtilsAndAssertionTests/ZenUnitUtilsAndAssertionTests --test-runs=2 --random --max-test-milliseconds=200')])
               os.chdir.assert_called_once_with('..')
            else:
               BuildAndTestZenUnitAndMetalMock.windows_cmake_build.assert_called_once_with(self.cmakeBuildType, self.cmakeDefinitions)
               Process.fail_fast_run.assert_has_calls([
                  call(f'MetalMockExamples/{self.cmakeBuildType}/MetalMockExamples.exe --random --max-test-milliseconds=200'),
                  call(f'MetalMockTests/{self.cmakeBuildType}/MetalMockTests.exe --random --max-test-milliseconds=200'),
                  call(f'ZenUnitCompileSpeedTests/{self.cmakeBuildType}/ZenUnitCompileSpeedTests.exe --random --max-test-milliseconds=200'),
                  call(f'ZenUnitExamples/{self.cmakeBuildType}/ZenUnitExamples.exe --random --max-test-milliseconds=200'),
                  call(f'ZenUnitLibraryTests/{self.cmakeBuildType}/ZenUnitLibraryTests.exe --random --max-test-milliseconds=200'),
                  call(f'ZenUnitUtilsAndAssertionTests/{self.cmakeBuildType}/ZenUnitUtilsAndAssertionTests.exe --random --max-test-milliseconds=200')])
               os.chdir.assert_not_called()
            self.assertEqual(0, exitCode)
      testcase('Linux', True)
      testcase('linux', True)
      testcase('Windows', False)
      testcase('OSX', False)

   def test_linux_cmake_and_build_RunsCMakes_RunsNinja(self):
      @patch('ZenUnitDevOpsPython.CMake.generate', spec_set=True)
      @patch('ZenUnitDevOpsPython.Process.fail_fast_run', spec_set=True)
      def testcase(cmakeDefinitions, expectedCMakeDefinitionsArgument, _1, _2):
         with self.subTest(f'{cmakeDefinitions, expectedCMakeDefinitionsArgument}'):
            #
            BuildAndTestZenUnitAndMetalMock.linux_cmake_build(self.cmakeBuildType, cmakeDefinitions)
            #
            CMake.generate.assert_called_once_with(self.cmakeBuildType, 'Ninja', self.cmakeBuildType, expectedCMakeDefinitionsArgument, '..')
            Process.fail_fast_run.assert_called_once_with('ninja -v')
      testcase('', '')
      testcase('-DOptionA=ON', '-DOptionA=ON')
      testcase('-DOptionB=ON', '-DOptionB=ON')

   def test_windows_cmake_build_RunsCMakes_RunsCMakeBuildToRunMSBuild(self):
      @patch('ZenUnitDevOpsPython.CMake.generate', spec_set=True)
      @patch('ZenUnitDevOpsPython.Process.fail_fast_run', spec_set=True)
      def testcase(cmakeDefinitions, expectedCMakeDefinitionsArgument, _1, _2):
         with self.subTest(f'{cmakeDefinitions, expectedCMakeDefinitionsArgument, }'):
            #
            BuildAndTestZenUnitAndMetalMock.windows_cmake_build(self.cmakeBuildType, cmakeDefinitions)
            #
            CMake.generate.assert_called_once_with('.', 'Visual Studio 18 2026', self.cmakeBuildType, expectedCMakeDefinitionsArgument, '.')
            expectedCMakeBuildCommand = f'cmake.exe --build . --config {self.cmakeBuildType}'
            Process.fail_fast_run.assert_called_once_with(expectedCMakeBuildCommand)
      testcase('', '')
      testcase('-DOptionA=ON', '-DOptionA=ON')
      testcase('-DOptionB=ON', '-DOptionB=ON')


if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(BuildZenUnitTests, testNames)
