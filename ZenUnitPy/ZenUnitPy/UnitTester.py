import unittest

def run_tests(testCaseType, testNames):
   textTestRunner = unittest.TextTestRunner(verbosity=3)
   testCaseMapObject = map(testCaseType, testNames)
   testSuite = unittest.TestSuite(testCaseMapObject)
   textTestRunner.run(testSuite)
