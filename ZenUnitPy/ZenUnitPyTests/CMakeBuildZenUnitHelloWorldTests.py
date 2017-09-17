import platform
import os
import unittest
from unittest.mock import patch
from ZenUnitPy import UnitTester, CMakeBuildZenUnit, CMakeBuildZenUnitHelloWorld, Util
import TestRandom

testNames = [
'main_ArgsLengthNot4_PrintsUsageAndExits1_test',
'main_ArgsLength4_CMakes_Builds_InstallsIfInstallDirectoryNotNoInstall_test'
]

class CMakeBuildZenUnitHelloWorldTests(unittest.TestCase):

   def setUp(self):
      self.generator = TestRandom.string()
      self.buildType = TestRandom.string()
      self.definitions = TestRandom.string()

   def main_ArgsLengthNot4_PrintsUsageAndExits1_test(self):
      @patch('ZenUnitPy.Util.print_and_exit', spec_set=True)
      def testcase(argsLength, _1):
         invalidArgs = ['arg'] * argsLength
         #
         CMakeBuildZenUnitHelloWorld.main(invalidArgs)
         #
         Util.print_and_exit.assert_called_once_with(
'Invalid args: ' + ' '.join(invalidArgs) + '\n' +
"""Usage: python3 CMakeBuildZenUnitHelloWorld.py --generator=<CMakeGenerator> --buildType=<CMakeBuildType> --definitions=<QuotedSpaceSeparatedCMakeDefinitions>""", 1)
      testcase(0)
      testcase(3)
      testcase(5)

   def main_ArgsLength4_CMakes_Builds_InstallsIfInstallDirectoryNotNoInstall_test(self):
      @patch('platform.system', spec_set=True)
      @patch('ZenUnitPy.CMakeBuildZenUnit.linux_cmake_and_build', spec_set=True)
      @patch('ZenUnitPy.CMakeBuildZenUnit.linux_run_zenunit_tests', spec_set=True)
      @patch('ZenUnitPy.CMakeBuildZenUnit.windows_cmake_and_build', spec_set=True)
      @patch('ZenUnitPy.CMakeBuildZenUnit.windows_run_zenunit_tests', spec_set=True)
      @patch('os.chdir', spec_true=True)
      def testcase(platformSystem, expectLinux, _1, _2, _3, _4, _5, _6):
         with self.subTest(f'{platformSystem}, {expectLinux}'):
            platform.system.return_value = platformSystem
            args = [ '.py', self.generator, self.buildType, self.definitions ]
            #
            CMakeBuildZenUnitHelloWorld.main(args)
            #
            platform.system.assert_called_once_with()
            if expectLinux:
               CMakeBuildZenUnit.linux_cmake_and_build.assert_called_once_with(self.generator, self.buildType, self.definitions)
               CMakeBuildZenUnit.linux_run_zenunit_tests.assert_called_once_with('ZenUnitHelloWorldTests')
               os.chdir.assert_called_once_with('..')
            else:
               CMakeBuildZenUnit.windows_cmake_and_build.assert_called_once_with(self.generator, self.buildType, self.definitions)
               CMakeBuildZenUnit.windows_run_zenunit_tests.assert_called_once_with(self.buildType, 'ZenUnitHelloWorldTests')
               os.chdir.assert_not_called()
      testcase('Linux', True)
      testcase('linux', True)
      testcase('Windows', False)
      testcase('OSX', False)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(CMakeBuildZenUnitHelloWorldTests, testNames)
