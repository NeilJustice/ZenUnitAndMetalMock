import glob
import os
import platform
import sys
import unittest
from unittest.mock import call, patch
from ZenUnitDevOpsPython import Python, Process
from ZenUnitDevOpsPythonTests import Random, UnitTester

testNames = [
'test_pylint_file_CallsPylintOnAllPythonFilesInCurrentFolderAndSubFolders',
'test_run_mypy_RunsMypyDot',
'test_run_pylint_on_all_files_in_parallel_LinuxCallsMapParallelPylintFileWithAllPyFilePaths_WindowsCallsMapSequential',
'test_run_flake8_RunsFlake8WithFlake8Config',
'test_run_all_with_coverage_RunsCoverage_RunsReport_RunsHtml_RunsXml_ExitsWithReportExitCode'
]

class PythonTests(unittest.TestCase):

   ExpectedPylintCommand = 'pylint --rcfile=.pylintrc --score=n '

   @patch('ZenUnitDevOpsPython.Process.run_and_get_exit_code', spec_set=True)
   def test_pylint_file_CallsPylintOnAllPythonFilesInCurrentFolderAndSubFolders(self, _1):
      pylintExitCode = Random.integer()
      Process.run_and_get_exit_code.return_value = pylintExitCode
      pythonFilePath = Random.string()
      #
      pylintExitCode = Python.pylint_file(pythonFilePath)
      #
      Process.run_and_get_exit_code.assert_called_once_with(PythonTests.ExpectedPylintCommand + pythonFilePath)
      self.assertEqual(pylintExitCode, pylintExitCode)

   @staticmethod
   @patch('ZenUnitDevOpsPython.Process.fail_fast_run', spec_set=True)
   def test_run_mypy_RunsMypyDot(_1):
      #
      Python.run_mypy()
      #
      Process.fail_fast_run('mypy .')

   def test_run_pylint_on_all_files_in_parallel_LinuxCallsMapParallelPylintFileWithAllPyFilePaths_WindowsCallsMapSequential(self):
      @patch('glob.glob', spec_set=True)
      @patch('platform.system', spec_set=True)
      @patch('ZenUnitDevOpsPython.Process.run_parallel_processpoolexecutor', spec_set=True)
      @patch('ZenUnitDevOpsPython.Process.run_parallel_processthread', spec_set=True)
      @patch('sys.exit', spec_set=True)
      def testcase(platformSystem, expectedMapParallel, allPylintsSucceeded, expectSysExit1, _1, _2, _3, _4, _5):
         with self.subTest(f'{platformSystem, expectedMapParallel, allPylintsSucceeded, expectSysExit1}'):
            pyFilePaths = [Random.string(), Random.string()]
            glob.glob.return_value = pyFilePaths
            platform.system.return_value = platformSystem
            if expectedMapParallel:
               Process.run_parallel_processpoolexecutor.return_value = allPylintsSucceeded
            else:
               Process.run_parallel_processthread.return_value = allPylintsSucceeded
            #
            Python.run_pylint_on_all_files_in_parallel()
            #
            glob.glob.assert_called_once_with('**/*.py', recursive=True)
            platform.system.assert_called_once_with()
            if expectedMapParallel:
               Process.run_parallel_processpoolexecutor.assert_called_once_with(Python.pylint_file, pyFilePaths)
               Process.run_parallel_processthread.assert_not_called()
            else:
               Process.run_parallel_processpoolexecutor.assert_not_called()
               Process.run_parallel_processthread.assert_called_once_with(PythonTests.ExpectedPylintCommand, pyFilePaths)
            if expectSysExit1:
               sys.exit.assert_called_once_with(1)
            else:
               sys.exit.assert_not_called()
      testcase('Linux', True, True, False)
      testcase('Windows', False, False, True)
      testcase('windows', True, False, True)

   @staticmethod
   @patch('ZenUnitDevOpsPython.Process.fail_fast_run', spec_set=True)
   def test_run_flake8_RunsFlake8WithFlake8Config(_1):
      #
      Python.run_flake8()
      #
      expectedFlake8Command = 'flake8 --config=.flake8 --show-source --benchmark'
      Process.fail_fast_run.assert_called_once_with(expectedFlake8Command)

   def test_run_all_with_coverage_RunsCoverage_RunsReport_RunsHtml_RunsXml_ExitsWithReportExitCode(self):
      @patch('os.getcwd', spec_set=True)
      @patch('ZenUnitDevOpsPython.Process.fail_fast_run', spec_set=True)
      @patch('ZenUnitDevOpsPython.Process.run_and_get_exit_code', spec_set=True)
      @patch('sys.exit', spec_set=True)
      @patch('builtins.print', spec_set=True)
      def testcase(reportExitCode, expectedConcludingPrint, printMock, _2, _3, _4, _5):
         currentWorkingDirectory = Random.string()
         os.getcwd.return_value = currentWorkingDirectory
         Process.run_and_get_exit_code.return_value = reportExitCode
         testsProjectName = Random.string()
         omitPattern = Random.string()
         #
         Python.run_all_with_coverage(testsProjectName, omitPattern)
         #
         self.assertEqual(2, len(printMock.call_args_list))
         printMock.assert_has_calls([call(f'Running {testsProjectName}/RunAll.py with coverage from', currentWorkingDirectory)])
         Process.run_and_get_exit_code.assert_called_once_with(
            f'coverage report --omit="{omitPattern}" --fail-under=100 --show-missing')
         self.assertEqual(3, len(Process.fail_fast_run.call_args_list))
         Process.fail_fast_run.assert_has_calls([
            call(f'coverage run --branch {testsProjectName}/RunAll.py'),
            call(f'coverage xml --omit="{omitPattern}" -o {testsProjectName}/CoberturaCodeCoverageResults_{testsProjectName}.xml'),
            call(f'coverage html --directory={testsProjectName}/CodeCoverageHTMLReport --title="{testsProjectName} Code Coverage"')])
         printMock.assert_has_calls([call(expectedConcludingPrint)])
         sys.exit.assert_called_once_with(reportExitCode)
      expectedFailureMessage = 'Failure. Code coverage is less than 100%.'
      testcase(-1, expectedFailureMessage)
      testcase(0, 'Success. Code coverage is 100%.')
      testcase(1, expectedFailureMessage)
      testcase(2, expectedFailureMessage)


if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(PythonTests, testNames)
