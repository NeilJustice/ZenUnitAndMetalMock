import glob
import os
import platform
import sys
import unittest
from unittest.mock import patch
from ZenUnitPy import Python, Process, UnitTester

testNames = [
'pylint_file_CallsPylintOnAllPythonFilesInCurrentFolderAndSubFolders_test',
'pylint_all_LinuxCallsMapParallelPylintFileWithAllPyFilePaths_WindowsCallsMapSequential_test',
'flake8_all_RunsFlake8WithFlake8Config_test'
]

class PythonTests(unittest.TestCase):

   @patch('ZenUnitPy.Process.run_and_get_exitcode', spec_set=True)
   def pylint_file_CallsPylintOnAllPythonFilesInCurrentFolderAndSubFolders_test(self, _1):
      PylintExitCode = 1
      Process.run_and_get_exitcode.return_value = PylintExitCode
      PythonFilePath = 'PythonFilePath'
      #
      pylintExitCode = Python.pylint_file(PythonFilePath)
      #
      expectedPylintCommand =\
         "pylint --rcfile=.pylintrc --score=n --init-hook=\"sys.path.append('.')\" {0}".format(PythonFilePath)
      Process.run_and_get_exitcode.assert_called_once_with(expectedPylintCommand)
      self.assertEqual(PylintExitCode, pylintExitCode)

   def pylint_all_LinuxCallsMapParallelPylintFileWithAllPyFilePaths_WindowsCallsMapSequential_test(self):
      @patch('glob.glob', spec_set=True)
      @patch('platform.system', spec_set=True)
      @patch('ZenUnitPy.Process.map_parallel', spec_set=True)
      @patch('ZenUnitPy.Process.map_sequential', spec_set=True)
      @patch('sys.exit', spec_set=True)
      def testcase(platformSystem, expectedMapParallel, allPylintsSucceeded, expectSysExit1, _1, _2, _3, _4, _5):
         with self.subTest(f'{platformSystem}, {expectedMapParallel}, {allPylintsSucceeded}, {expectSysExit1}'):
            Process.map_parallel.reset_mock()
            Process.map_sequential.reset_mock()
            PyFilePaths = ['a.py', 'b.py']
            glob.glob.return_value = PyFilePaths
            platform.system.return_value = platformSystem
            if expectedMapParallel:
               Process.map_parallel.return_value = allPylintsSucceeded
            else:
               Process.map_sequential.return_value = allPylintsSucceeded
            #
            Python.pylint_all()
            #
            glob.glob.assert_called_once_with('**/*.py', recursive=True)
            platform.system.assert_called_once_with()
            if expectedMapParallel:
               Process.map_parallel.assert_called_once_with(Python.pylint_file, PyFilePaths)
               Process.map_sequential.assert_not_called()
            else:
               Process.map_parallel.assert_not_called()
               Process.map_sequential.assert_called_once_with(Python.pylint_file, PyFilePaths)
            if expectSysExit1:
               sys.exit.assert_called_once_with(1)
            else:
               sys.exit.assert_not_called()
      testcase('Linux', True, True, False)
      testcase('Windows', False, False, True)
      testcase('windows', True, False, True)

   @patch('ZenUnitPy.Process.run', spec_set=True)
   def flake8_all_RunsFlake8WithFlake8Config_test(self, _1):
      JoinReturnValue = 'JoinReturnValue'
      os.path.join.return_value = JoinReturnValue
      #
      Python.flake8_all()
      #
      expectedFlake8Command = 'flake8 --benchmark --config=.flake8 --show-source'
      Process.run.assert_called_once_with(expectedFlake8Command)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(PythonTests, testNames)
