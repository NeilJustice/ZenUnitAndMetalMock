import os
import platform
import sys
import unittest
from unittest.mock import call, patch
sys.path.append('..') # Jenkins
from ZenUnitPy import ArgParser, CMake, BuildAndInstallZenUnitAndMetalMock, Process, UnitTester, Util
import Random

testNames = [
'main_ArgsLengthIsNot5_PrintsUsageAndExits1_test',
'main_ArgsLengthIs5_CMakes_Builds_Installs_test',
'linux_cmake_and_build_CMakes_BuildsWithNinja_RunsCMakeInstall_test',
'windows_cmake_build_install_CMakes_BuildsWithMSBuild_RunsCMakeInstall_test',
]

class BuildAndInstallZenUnitTests(unittest.TestCase):

   def setUp(self):
      self.cmakeGenerator = Random.string()
      self.cmakeArchitecture = Random.string()
      self.cmakeBuildType = Random.string()
      self.cmakeDefinitions = Random.string()

   def main_ArgsLengthIsNot5_PrintsUsageAndExits1_test(self):
      @patch('ZenUnitPy.Util.print_and_exit', spec_set=True)
      def testcase(argsLength, _1):
         with self.subTest(f'{argsLength}'):
            invalidArgs = [Random.string()] * argsLength
            #
            BuildAndInstallZenUnitAndMetalMock.main(invalidArgs)
            #
            Util.print_and_exit.assert_called_once_with(
'Invalid args: ' + ' '.join(invalidArgs) + '\n'
"""Usage: python BuildAndInstallZenUnitAndMetalMock.py --cmake-generator=<CMakeGenerator> --cmake-architecture=<x64OrWin32> --cmake-build-type=<CMakeBuildType> --cmake-definitions=<QuotedSpaceSeparatedCMakeDefinitions>""", 1)
      testcase(0)
      testcase(1)
      testcase(2)
      testcase(3)
      testcase(4)
      testcase(6)

   def main_ArgsLengthIs5_CMakes_Builds_Installs_test(self):
      @patch('platform.system', spec_set=True)
      @patch('ZenUnitPy.ArgParser.parse_arg', spec_set=True)
      @patch('ZenUnitPy.BuildAndInstallZenUnitAndMetalMock.linux_cmake_build_install', spec_set=True)
      @patch('ZenUnitPy.BuildAndInstallZenUnitAndMetalMock.windows_cmake_build_install', spec_set=True)
      @patch('ZenUnitPy.Process.run', spec_set=True)
      @patch('os.chdir', spec_true=True)
      def testcase(platformSystem, expectLinux, _1, _2, _3, _4, _5, _6):
         with self.subTest(f'{platformSystem}, {expectLinux}'):
            ArgParser.parse_arg.side_effect = [self.cmakeGenerator, self.cmakeArchitecture, self.cmakeBuildType, self.cmakeDefinitions]
            platform.system.return_value = platformSystem
            args = [Random.string(), Random.string(), Random.string(), Random.string(), Random.string()]
            #
            BuildAndInstallZenUnitAndMetalMock.main(args)
            #
            self.assertEqual(4, len(ArgParser.parse_arg.call_args_list))
            ArgParser.parse_arg.assert_has_calls([
               call('--cmake-generator', args[1]),
               call('--cmake-architecture', args[2]),
               call('--cmake-build-type', args[3]),
               call('--cmake-definitions', args[4])
            ])
            platform.system.assert_called_once_with()
            if expectLinux:
               BuildAndInstallZenUnitAndMetalMock.linux_cmake_build_install.assert_called_once_with(self.cmakeGenerator, self.cmakeArchitecture, self.cmakeBuildType, self.cmakeDefinitions)
               self.assertEqual(3, len(Process.run.call_args_list))
               Process.run.assert_has_calls([
                  call('MetalMockTests/MetalMockTests'),
                  call('ZenUnitLibraryTests/ZenUnitLibraryTests'),
                  call('ZenUnitUtilsAndAssertionTests/ZenUnitUtilsAndAssertionTests')])
               os.chdir.assert_called_once_with('..')
            else:
               BuildAndInstallZenUnitAndMetalMock.windows_cmake_build_install.assert_called_once_with(self.cmakeGenerator, self.cmakeArchitecture, self.cmakeBuildType, self.cmakeDefinitions)
               Process.run.assert_not_called()
               os.chdir.assert_not_called()
      testcase('Linux', True)
      testcase('linux', True)
      testcase('Windows', False)
      testcase('OSX', False)

   def linux_cmake_and_build_CMakes_BuildsWithNinja_RunsCMakeInstall_test(self):
      @patch('ZenUnitPy.CMake.generate', spec_set=True)
      @patch('ZenUnitPy.Process.run', spec_set=True)
      @patch('ZenUnitPy.CMake.install', spec_set=True)
      def testcase(cmakeDefinitions, expectedCMakeDefinitionsArgument, _1, _2, _3):
         with self.subTest(f'{cmakeDefinitions, expectedCMakeDefinitionsArgument}'):
            #
            BuildAndInstallZenUnitAndMetalMock.linux_cmake_build_install(self.cmakeGenerator, self.cmakeArchitecture, self.cmakeBuildType, cmakeDefinitions)
            #
            CMake.generate.assert_called_once_with(
               self.cmakeBuildType, self.cmakeGenerator, self.cmakeArchitecture, self.cmakeBuildType, expectedCMakeDefinitionsArgument, '..')
            Process.run.assert_called_once_with('ninja -v')
            CMake.install.assert_called_once_with()
      testcase('', '')
      testcase('-DSanitizerMode=ON', '-DSanitizerMode=ON')
      testcase('-DOption=ON', '-DOption=ON')

   def windows_cmake_build_install_CMakes_BuildsWithMSBuild_RunsCMakeInstall_test(self):
      @patch('ZenUnitPy.CMake.generate', spec_set=True)
      @patch('ZenUnitPy.Process.run', spec_set=True)
      @patch('ZenUnitPy.CMake.install', spec_set=True)
      def testcase(cmakeDefinitions, expectedCMakeDefinitionsArgument, _1, _2, _3):
         with self.subTest(f'{cmakeDefinitions, expectedCMakeDefinitionsArgument, }'):
            #
            BuildAndInstallZenUnitAndMetalMock.windows_cmake_build_install(self.cmakeGenerator, self.cmakeArchitecture, self.cmakeBuildType, cmakeDefinitions)
            #
            CMake.generate.assert_called_once_with('.', self.cmakeGenerator, self.cmakeArchitecture, self.cmakeBuildType, expectedCMakeDefinitionsArgument, '.')
            expectedCMakeBuildCommand = 'cmake --build . --config {0}'.format(self.cmakeBuildType)
            Process.run.assert_called_once_with(expectedCMakeBuildCommand)
            CMake.install.assert_called_once_with()
      testcase('', '')
      testcase('-DSanitizerMode=ON', '-DSanitizerMode=ON')
      testcase('-DOption=ON', '-DOption=ON')

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(BuildAndInstallZenUnitTests, testNames)
