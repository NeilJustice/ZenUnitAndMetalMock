import os
import platform
import sys
import unittest
from unittest.mock import call, patch
sys.path.append('..') # Jenkins
from ZenUnitPy import ArgParser, CMake, BuildZenUnit, Process, UnitTester, Util, FileSystem
import Random

testNames = [
'main_ArgsLengthNot5_PrintsUsageAndExits1_test',
'main_ArgsLength5_CMakes_Builds_RunsTestsIfLinuxOtherwisePostBuildStepRunsTestsOnWindows_InstallsIfInstallDirectoryNotNoInstall_test',
'linux_cmake_and_build_CMakes_BuildsWithNinja_test',
'install_if_debug_and_install_dir_specified_RunsCMakeInstallIfDebugAndInstallDirectoryNotNoInstall_test',
'windows_cmake_and_build_CMakes_BuildsWithMSBuild_test',
]

class BuildZenUnitTests(unittest.TestCase):

   def setUp(self):
      self.cmakeGenerator = Random.string()
      self.cmakeBuildType = Random.string()
      self.cmakeDefinitions = Random.string()
      self.installDirectory = Random.string()

   def main_ArgsLengthNot5_PrintsUsageAndExits1_test(self):
      @patch('ZenUnitPy.Util.print_and_exit', spec_set=True)
      def testcase(argsLength, _1):
         with self.subTest(f'{argsLength}'):
            invalidArgs = [Random.string()] * argsLength
            #
            BuildZenUnit.main(invalidArgs)
            #
            Util.print_and_exit.assert_called_once_with(
'Invalid args: ' + ' '.join(invalidArgs) + '\n' +
"""Usage: python3 BuildZenUnit.py --generator=<CMakeGenerator> --buildType=<CMakeBuildType> --definitions=<QuotedSpaceSeparatedCMakeDefinitions> --installDirectory=<DirectoryOrNoInstall>""", 1)
      testcase(0)
      testcase(4)
      testcase(6)

   def main_ArgsLength5_CMakes_Builds_RunsTestsIfLinuxOtherwisePostBuildStepRunsTestsOnWindows_InstallsIfInstallDirectoryNotNoInstall_test(self):
      @patch('platform.system', spec_set=True)
      @patch('ZenUnitPy.ArgParser.parse_arg', spec_set=True)
      @patch('ZenUnitPy.BuildZenUnit.linux_cmake_and_build', spec_set=True)
      @patch('ZenUnitPy.BuildZenUnit.windows_cmake_and_build', spec_set=True)
      @patch('ZenUnitPy.Process.run', spec_set=True)
      @patch('ZenUnitPy.BuildZenUnit.install_if_debug_and_install_dir_specified', spec_true=True)
      @patch('os.chdir', spec_true=True)
      def testcase(platformSystem, expectLinux, _1, _2, _3, _4, _5, _6, _7):
         with self.subTest(f'{platformSystem}, {expectLinux}'):
            ArgParser.parse_arg.side_effect = [ self.cmakeGenerator, self.cmakeBuildType, self.cmakeDefinitions, self.installDirectory ]
            platform.system.return_value = platformSystem
            args = [ Random.string(), self.cmakeGenerator, self.cmakeBuildType, self.cmakeDefinitions, self.installDirectory ]
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
               BuildZenUnit.linux_cmake_and_build.assert_called_once_with(
                  self.cmakeGenerator, self.cmakeBuildType, self.cmakeDefinitions, self.installDirectory)
               Process.run.assert_called_once_with('ZenUnitTests/ZenUnitTests')
               BuildZenUnit.install_if_debug_and_install_dir_specified.assert_called_once_with(
                  self.cmakeBuildType, self.installDirectory)
               os.chdir.assert_called_once_with('..')
            else:
               BuildZenUnit.windows_cmake_and_build.assert_called_once_with(
                  self.cmakeGenerator, self.cmakeBuildType, self.cmakeDefinitions, self.installDirectory)
               Process.run.assert_not_called()
               BuildZenUnit.install_if_debug_and_install_dir_specified.assert_called_once_with(
                  self.cmakeBuildType, self.installDirectory)
               os.chdir.assert_not_called()
      testcase('Linux', True)
      testcase('linux', True)
      testcase('Windows', False)
      testcase('OSX', False)

   def linux_cmake_and_build_CMakes_BuildsWithNinja_test(self):
      @patch('ZenUnitPy.CMake.generate', spec_set=True)
      @patch('ZenUnitPy.Process.run', spec_set=True)
      def testcase(cmakeDefinitions, installDirectory, expectedCMakeDefinitionsArgument, _1, _2):
         with self.subTest(f'{cmakeDefinitions, installDirectory, expectedCMakeDefinitionsArgument}'):
            #
            BuildZenUnit.linux_cmake_and_build(
               self.cmakeGenerator, self.cmakeBuildType, cmakeDefinitions, installDirectory)
            #
            CMake.generate.assert_called_once_with(
               self.cmakeBuildType, self.cmakeGenerator, self.cmakeBuildType, expectedCMakeDefinitionsArgument, '..')
            Process.run.assert_called_once_with('ninja -v')
      testcase('', '', f' -DCMAKE_INSTALL_PREFIX=')
      testcase('-DSanitizerMode=ON', '', '-DSanitizerMode=ON -DCMAKE_INSTALL_PREFIX=')
      testcase('-DSanitizerMode=ON', 'NoInstall', '-DSanitizerMode=ON')
      testcase('-DSanitizerMode=ON', 'noinstall', '-DSanitizerMode=ON')
      testcase('-DSanitizerMode=ON', '/home/user/directory', '-DSanitizerMode=ON -DCMAKE_INSTALL_PREFIX=/home/user/directory')
      testcase('', '/usr/local', ' -DCMAKE_INSTALL_PREFIX=/usr/local')

   def install_if_debug_and_install_dir_specified_RunsCMakeInstallIfDebugAndInstallDirectoryNotNoInstall_test(self):
      @patch('ZenUnitPy.Process.run', spec_true=True)
      @patch('ZenUnitPy.FileSystem.delete_folder_if_exists', spec_set=True)
      @patch('os.path.join', spec_set=True)
      def testcase(installDirectory, cmakeBuildType, expectCallToCMakeInstall, _1, _2, _3):
         with self.subTest(f'{installDirectory}, {expectCallToCMakeInstall}'):
            osJoinReturnValue = Random.string()
            os.path.join.return_value = osJoinReturnValue
            #
            BuildZenUnit.install_if_debug_and_install_dir_specified(cmakeBuildType, installDirectory)
            #
            if expectCallToCMakeInstall:
               os.path.join.assert_called_once_with(installDirectory, 'include', 'ZenUnit')
               expectedZenUnitIncludeDirectory = osJoinReturnValue
               FileSystem.delete_folder_if_exists.assert_called_once_with(expectedZenUnitIncludeDirectory)
               expectedInstallCommand = f'cmake --build . --target install --config {cmakeBuildType}'
               Process.run.assert_called_once_with(expectedInstallCommand)
            else:
               os.path.join.assert_not_called()
               FileSystem.delete_folder_if_exists.assert_not_called()
               Process.run.assert_not_called()
      testcase('/usr/local', 'Debug', True)
      testcase('~/install', 'Debug', True)
      testcase('C:\\install', 'Debug', True)
      testcase('noinstall', 'Debug', True)
      testcase('NoInstall', 'Debug', False)
      testcase('/usr/local', 'debug', False)
      testcase('/usr/local', 'Release', False)
      testcase('NoInstall', 'Release', False)

   def windows_cmake_and_build_CMakes_BuildsWithMSBuild_test(self):
      @patch('ZenUnitPy.CMake.generate', spec_set=True)
      @patch('ZenUnitPy.Process.run', spec_set=True)
      def testcase(cmakeDefinitions, installDirectory, expectedCMakeDefinitionsArgument, _1, _2):
         with self.subTest(f'{cmakeDefinitions, installDirectory, expectedCMakeDefinitionsArgument, }'):
            #
            BuildZenUnit.windows_cmake_and_build(self.cmakeGenerator, self.cmakeBuildType, cmakeDefinitions, installDirectory)
            #
            CMake.generate.assert_called_once_with('.', self.cmakeGenerator, self.cmakeBuildType, expectedCMakeDefinitionsArgument, '.')
            expectedCMakeBuildCommand = 'cmake --build . --config {0}'.format(self.cmakeBuildType)
            Process.run.assert_called_once_with(expectedCMakeBuildCommand)
      testcase('', '', f' -DCMAKE_INSTALL_PREFIX=')
      testcase('-DSanitizerMode=ON', '', '-DSanitizerMode=ON -DCMAKE_INSTALL_PREFIX=')
      testcase('-DSanitizerMode=ON', 'NoInstall', '-DSanitizerMode=ON')
      testcase('-DSanitizerMode=ON', 'noinstall', '-DSanitizerMode=ON')
      testcase('-DSanitizerMode=ON', 'C:\\Users\\UserName\\install', '-DSanitizerMode=ON -DCMAKE_INSTALL_PREFIX=C:\\Users\\UserName\\install')
      testcase('', 'C:\\install', ' -DCMAKE_INSTALL_PREFIX=C:\\install')

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(BuildZenUnitTests, testNames)
