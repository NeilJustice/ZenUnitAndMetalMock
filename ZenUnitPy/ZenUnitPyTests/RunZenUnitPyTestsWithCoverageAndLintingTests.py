import os
import platform
import unittest
from unittest.mock import patch
from unittest.mock import call
from ZenUnitPy import RunZenUnitPyTestsWithCoverageAndLinting, Process, Python, UnitTester
from ZenUnitPyTests import Random

testNames = ['main_ParsesArgs_RunAllTestsWithCoverage_PylintsAll_Flake8sAll_test']

class RunZenUnitPyTestsWithCoverageAndLintingTests(unittest.TestCase):

   def main_ParsesArgs_RunAllTestsWithCoverage_PylintsAll_Flake8sAll_test(self):
      @patch('os.chdir', spec_set=True)
      @patch('platform.system', spec_set=True)
      @patch('ZenUnitPy.Process.run', spec_set=True)
      @patch('ZenUnitPy.Python.pylint_all', spec_set=True)
      @patch('ZenUnitPy.Python.flake8_all', spec_set=True)
      def testcase(platformSystem, expectedPythonExecutableName, _1, _2, _3, _4, _5):
         with self.subTest(f'{platformSystem}, {expectedPythonExecutableName}'):
            platform.system.return_value = platformSystem
            #
            RunZenUnitPyTestsWithCoverageAndLinting.main()
            #
            self.assertEqual(2, len(os.chdir.call_args_list))
            os.chdir.assert_has_calls([
               call('ZenUnitPy/ZenUnitPyTests'),
               call('..')])
            Process.run.assert_called_once_with(f'{expectedPythonExecutableName} -u RunAllWithCoverage.py')
            Python.pylint_all.assert_called_once_with()
            Python.flake8_all.assert_called_once_with()
      testcase('Linux', 'python3')
      testcase('linux', 'python3')
      testcase('Windows', 'python.exe')
      testcase('windows', 'python.exe')

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(RunZenUnitPyTestsWithCoverageAndLintingTests, testNames)
