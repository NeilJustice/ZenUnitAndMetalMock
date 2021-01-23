import platform
import unittest
from unittest.mock import patch
from ZenUnitPy import RunZenUnitPyTestsWithCoverageAndLinting, Process, Python, UnitTester

testNames = ['main_ParsesArgs_RunAllTestsWithCoverage_PylintsAll_Flake8sAll_test']

class RunZenUnitPyTestsWithCoverageAndLintingTests(unittest.TestCase):

   def main_ParsesArgs_RunAllTestsWithCoverage_PylintsAll_Flake8sAll_test(self):
      @patch('platform.system', spec_set=True)
      @patch('ZenUnitPy.Process.run', spec_set=True)
      @patch('ZenUnitPy.Python.pylint_all', spec_set=True)
      @patch('ZenUnitPy.Python.flake8_all', spec_set=True)
      def testcase(platformSystem, expectedPythonExecutableName, _1, _2, _3, _4):
         with self.subTest(f'{platformSystem}, {expectedPythonExecutableName}'):
            platform.system.return_value = platformSystem
            #
            RunZenUnitPyTestsWithCoverageAndLinting.main()
            #
            Process.run.assert_called_once_with(f'{expectedPythonExecutableName} -u ZenUnitPyTests/RunAllWithCoverage.py')
            Python.pylint_all.assert_called_once_with()
            Python.flake8_all.assert_called_once_with()
      testcase('Linux', 'python')
      testcase('linux', 'python')
      testcase('Windows', 'python.exe')
      testcase('windows', 'python.exe')

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(RunZenUnitPyTestsWithCoverageAndLintingTests, testNames)
