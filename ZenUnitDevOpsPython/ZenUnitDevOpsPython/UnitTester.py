import unittest
from typing import Any, List

def run_tests(testCaseType: Any, testNames: List[str]) -> None:
   textTestRunner = unittest.TextTestRunner(verbosity=3)
   testCaseMapObject = map(testCaseType, testNames)
   testSuite = unittest.TestSuite(testCaseMapObject)
   textTestRunner.run(testSuite)
