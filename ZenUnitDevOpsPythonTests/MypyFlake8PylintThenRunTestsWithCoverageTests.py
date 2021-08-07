import unittest
from unittest.mock import call, patch
from ZenUnitDevOpsPython import MypyFlake8PylintThenRunTestsWithCoverage, Process, Python, UnitTester

testNames = ['test_main_ParsesArgs_RunsMypy_RunsFlake8_RunsPylint_RunsAllTestsWithCoverage']

class RunZenUnitDevOpsPythonTestsWithCoverageAndLintingTests(unittest.TestCase):

   @patch('builtins.print', spec_set=True)
   @patch('ZenUnitDevOpsPython.Python.run_mypy', spec_set=True)
   @patch('ZenUnitDevOpsPython.Python.run_flake8', spec_set=True)
   @patch('ZenUnitDevOpsPython.Python.run_pylint_on_all_files_in_parallel', spec_set=True)
   @patch('ZenUnitDevOpsPython.Process.fail_fast_run', spec_set=True)
   def test_main_ParsesArgs_RunsMypy_RunsFlake8_RunsPylint_RunsAllTestsWithCoverage(self, _1, _2, _3, _4, printMock):
      #
      MypyFlake8PylintThenRunTestsWithCoverage.main()
      #
      Python.run_mypy.assert_called_once_with()
      Python.run_flake8.assert_called_once_with()
      Python.run_pylint_on_all_files_in_parallel.assert_called_once_with()
      Process.fail_fast_run.assert_called_once_with('python -u ZenUnitDevOpsPythonTests/RunAllWithCoverage.py')
      self.assertEqual(3, len(printMock.call_args_list))
      printMock.assert_has_calls([
         call('[MypyFlake8PylintThenRunTestsWithCoverage.py] Running Mypy, Flake8, Pylint, then running tests with coverage...'),
         call('[MypyFlake8PylintThenRunTestsWithCoverage.py] Successfully ran mypy, flake8, pylint, and unit tests with code coverage.'),
         call('[MypyFlake8PylintThenRunTestsWithCoverage.py] ExitCode: 0')])

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(RunZenUnitDevOpsPythonTestsWithCoverageAndLintingTests, testNames)
