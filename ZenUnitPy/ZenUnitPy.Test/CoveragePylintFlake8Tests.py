import os
import unittest
from unittest.mock import patch
from unittest.mock import call
from ZenUnitPy import CoveragePylintFlake8, Process, Python, UnitTester, Util

testNames = [
'main_ArgsLengthNot3_PrintsUsageAndExits1_test',
'main_ArgsLength3_RunTestsWithCoverage_PylintsAll_Flake8sAll_test' ]

class CoveragePylintFlake8Tests(unittest.TestCase):

   def main_ArgsLengthNot3_PrintsUsageAndExits1_test(self):
      @patch('ZenUnitPy.Util.print_and_exit')
      def testcase(argsLength, _1):
         CoveragePylintFlake8.main(['arg'] * argsLength)
         Util.print_and_exit.assert_called_once_with(
            'Usage: python3 CoveragePylintFlake8.py <TestProjectFolderName> <RunAllWithCoveragePyFileName>', 1)
      testcase(0)
      testcase(2)
      testcase(4)

   @patch('os.chdir', spec_set=True)
   @patch('ZenUnitPy.Process.run', spec_set=True)
   @patch('ZenUnitPy.Python.pylint_all', spec_set=True)
   @patch('ZenUnitPy.Python.flake8_all', spec_set=True)
   def main_ArgsLength3_RunTestsWithCoverage_PylintsAll_Flake8sAll_test(self, _1, _2, _3, _4):
      TestProjectFolderName = 'Project.Test'
      RunAllWithCoveragePyFileName = 'RunAllWithCoverage.py'
      Args = ['.py', TestProjectFolderName, RunAllWithCoveragePyFileName]
      #
      CoveragePylintFlake8.main(Args)
      #
      self.assertEqual(2, len(os.chdir.call_args_list))
      os.chdir.assert_has_calls([
         call(TestProjectFolderName),
         call('..')])
      expectedRunTestsWithCoverageCommand = 'python3 ' + RunAllWithCoveragePyFileName
      Process.run.assert_called_once_with(expectedRunTestsWithCoverageCommand)
      Python.pylint_all.assert_not_called()
      Python.flake8_all.assert_called_once_with()

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(CoveragePylintFlake8Tests, testNames)
