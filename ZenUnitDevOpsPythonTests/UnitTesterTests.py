import unittest
from unittest.mock import Mock, patch, sentinel
from ZenUnitDevOpsPython import UnitTester
from ZenUnitDevOpsPythonTests import Random

testNames = ['test_run_tests_RunsTestSuiteWithTextTestRunner']

class UnitTesterTests(unittest.TestCase):

   @patch('unittest.TextTestRunner', spec_set=True)
   @patch('builtins.map', spec_set=True)
   @patch('unittest.TestSuite', spec_set=True)
   def test_run_tests_RunsTestSuiteWithTextTestRunner(self, _1, _2, _3):
      textTestRunnerMock = Mock(spec=['run'])
      unittest.TextTestRunner.return_value = textTestRunnerMock
      map.return_value = sentinel.testCaseMapObject
      unittest.TestSuite.return_value = sentinel.testSuite
      testCaseName = Random.string()
      testingTestNames = [Random.string(), Random.string()]
      #
      UnitTester.run_tests(testCaseName, testingTestNames)
      #
      unittest.TextTestRunner.assert_called_once_with(verbosity=3)
      map.assert_called_once_with(testCaseName, testingTestNames)
      unittest.TestSuite.assert_called_once_with(sentinel.testCaseMapObject)
      textTestRunnerMock.run.assert_called_once_with(sentinel.testSuite)

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(UnitTesterTests, testNames)
