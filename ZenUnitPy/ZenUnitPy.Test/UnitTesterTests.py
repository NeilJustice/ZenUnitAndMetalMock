import unittest
from unittest.mock import Mock, patch, sentinel
from ZenUnitPy import UnitTester

testNames = [
'run_tests_RunsTestSuiteWithTextTestRunner_test' ]

class UnitTesterTests(unittest.TestCase):

   @patch('unittest.TextTestRunner', spec_set=True)
   @patch('builtins.map', spec_set=True)
   @patch('unittest.TestSuite', spec_set=True)   
   def run_tests_RunsTestSuiteWithTextTestRunner_test(self, _1, _2, _3):
      textTestRunnerMock = Mock(spec=['run'])
      unittest.TextTestRunner.return_value = textTestRunnerMock
      map.return_value = sentinel.testCaseMapObject
      unittest.TestSuite.return_value = Mock(spec=[''])
      TestCaseName = 'WidgetTests'
      TestNames = ['A_Test', 'B_Test']
      #
      UnitTester.run_tests(TestCaseName, TestNames)
      #
      unittest.TextTestRunner.assert_called_once_with(verbosity=3)
      map.assert_called_once_with(TestCaseName, TestNames)
      unittest.TestSuite.assert_called_once_with(sentinel.testCaseMapObject)
      textTestRunnerMock.run.assert_called_once_with(unittest.TestSuite.return_value)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(UnitTesterTests, testNames)
