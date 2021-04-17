import unittest
from unittest.mock import patch
from ZenUnitPy import RunZenUnitPyTestsWithCoverageAndLinting, Process, Python, UnitTester

testNames = ['test_main_ParsesArgs_RunsMypy_RunsFlake8_RunsPylint_RunsAllTestsWithCoverage']

class RunZenUnitPyTestsWithCoverageAndLintingTests(unittest.TestCase):

   @patch('platform.system', spec_set=True)
   @patch('ZenUnitPy.Process.fail_fast_run', spec_set=True)
   @patch('ZenUnitPy.Python.pylint_all', spec_set=True)
   @patch('ZenUnitPy.Python.flake8_all', spec_set=True)
   def test_main_ParsesArgs_RunsMypy_RunsFlake8_RunsPylint_RunsAllTestsWithCoverage(self, _1, _2, _3, _4):
      #
      RunZenUnitPyTestsWithCoverageAndLinting.main()
      #
      Python.flake8_all.assert_called_once_with()
      Python.pylint_all.assert_called_once_with()
      Process.fail_fast_run.assert_called_once_with('python -u ZenUnitPyTests/RunAllWithCoverage.py')

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(RunZenUnitPyTestsWithCoverageAndLintingTests, testNames)
