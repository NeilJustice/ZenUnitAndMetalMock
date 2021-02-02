import sys
import unittest
from unittest.mock import patch
import Random
from ZenUnitPy import UnitTester, Util

testNames = ['print_and_exit_PrintsMessageThenCallsExitWithExitCode_test']

class UtilTests(unittest.TestCase):

   @patch('sys.exit', spec_set=True)
   @patch('builtins.print', spec_set=True)
   def print_and_exit_PrintsMessageThenCallsExitWithExitCode_test(self, printMock, _2):
      message = Random.string()
      exitCode = Random.integer()
      #
      Util.print_and_exit(message, exitCode)
      #
      printMock.assert_called_once_with(message)
      sys.exit.assert_called_once_with(exitCode)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(UtilTests, testNames)
