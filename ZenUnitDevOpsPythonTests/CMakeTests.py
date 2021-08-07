import os
import platform
import unittest
from unittest.mock import patch
from ZenUnitDevOpsPython import CMake, Process, UnitTester

testNames = [
'test_generate_CreatesAndCdsToDirectory_RunsCMakeWithGeneratorAndBuildType'
]

class CMakeTests(unittest.TestCase):

   def test_generate_CreatesAndCdsToDirectory_RunsCMakeWithGeneratorAndBuildType(self):
      @patch('os.makedirs', spec_set=True)
      @patch('os.chdir', spec_set=True)
      @patch('platform.system', spec_set=True)
      @patch('ZenUnitDevOpsPython.Process.fail_fast_run', spec_set=True)
      @patch('builtins.print', spec_set=True)
      def testcase(platformSystem, cmakeDefinitions, expectedCMakeCommand, printMock, _2, _3, _4, _5):
         with self.subTest(f'{platformSystem}, {cmakeDefinitions}, {expectedCMakeCommand}'):
            platform.system.return_value = platformSystem
            folderPath = ''
            generator = 'Generator'
            buildType = 'BuildType'
            cmakeListsFolderPath = 'CMakeListsFolderPath'
            #
            CMake.generate(folderPath, generator, buildType, cmakeDefinitions, cmakeListsFolderPath)
            #
            os.makedirs.assert_called_once_with(folderPath, exist_ok=True)
            os.chdir.assert_called_once_with(folderPath)
            printMock.assert_called_once_with('Generating CMake in folder', folderPath)
            Process.fail_fast_run.assert_called_once_with(expectedCMakeCommand)
      testcase('Linux', '', 'cmake -G"Generator" -DCMAKE_BUILD_TYPE=BuildType  CMakeListsFolderPath')
      testcase('Linux', '-DSanitizersMode=ON', 'cmake -G"Generator" -DCMAKE_BUILD_TYPE=BuildType -DSanitizersMode=ON CMakeListsFolderPath')
      testcase('linux', '', 'cmake -G"Generator" -Ax64  CMakeListsFolderPath')
      testcase('Windows', '', 'cmake -G"Generator" -Ax64  CMakeListsFolderPath')
      testcase('Windows', '-DCMAKE_INSTALL_PREFIX=C:/', 'cmake -G"Generator" -Ax64 -DCMAKE_INSTALL_PREFIX=C:/ CMakeListsFolderPath')

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(CMakeTests, testNames)
