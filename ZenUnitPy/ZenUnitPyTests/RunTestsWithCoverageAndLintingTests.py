import os
import unittest
from unittest.mock import patch
from unittest.mock import call
from ZenUnitPy import RunTestsWithCoverageAndLinting, Process, Python, UnitTester
import Random

testNames = ['main_ParsesArgs_RunAllTestsWithCoverage_PylintsAll_Flake8sAll_test']

class RunTestsWithCoverageAndLintingTests(unittest.TestCase):

   ExpectedUsage = 'Usage: python3 RunTestsWithCoverageAndLinting.py --testProjectFolderPath=<FolderName> --runAllWithCoveragePyFileName=<FileName>'

   @patch('os.chdir', spec_set=True)
   @patch('ZenUnitPy.Process.run', spec_set=True)
   @patch('ZenUnitPy.Python.pylint_all', spec_set=True)
   @patch('ZenUnitPy.Python.flake8_all', spec_set=True)
   def main_ParsesArgs_RunAllTestsWithCoverage_PylintsAll_Flake8sAll_test(self, _1, _2, _3, _4):
      args = [Random.string(), Random.string(), Random.string()]
      #
      RunTestsWithCoverageAndLinting.main(args)
      #
      self.assertEqual(2, len(os.chdir.call_args_list))
      os.chdir.assert_has_calls([
         call('ZenUnitPy/ZenUnitPyTests'),
         call('..')])
      Process.run.assert_called_once_with('python3 RunAllWithCoverage.py')
      Python.pylint_all.assert_called_once_with()
      Python.flake8_all.assert_called_once_with()

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(RunTestsWithCoverageAndLintingTests, testNames)
