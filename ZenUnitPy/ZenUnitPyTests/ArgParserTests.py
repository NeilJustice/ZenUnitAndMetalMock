import unittest
from ZenUnitPy import ArgParser, UnitTester

testNames = [
'test_parse_arg_argValueDoesNotStartWithArgNameEqualsSign_raises',
'test_parse_arg_argValueStartsWithArgNameEqualsSign_ReturnsStringToTheRightOfFirstEqualsSign',
]

class ArgParserTests(unittest.TestCase):

   def test_parse_arg_argValueDoesNotStartWithArgNameEqualsSign_raises(self):
      def testcase(argName, argValue):
         with self.subTest(f'{argName}, {argValue}'):
            self.assertRaisesRegex(ValueError, f"Argument '{argValue}' does not start with '{argName}='", ArgParser.parse_arg, argName, argValue)
      testcase('', '')
      testcase('-argName', 'abc')
      testcase('--argName', '')
      testcase('--argName', '--argName')
      testcase('--argName', '--notArgName=1')
      testcase('--argName', '--argname=1')

   def test_parse_arg_argValueStartsWithArgNameEqualsSign_ReturnsStringToTheRightOfFirstEqualsSign(self):
      def testcase(argName, argValue, expectedReturnValue):
         with self.subTest(f'{argName}, {argValue}, {expectedReturnValue}'):
            parsedArgument = ArgParser.parse_arg(argName, argValue)
            self.assertEqual(expectedReturnValue, parsedArgument)
      testcase('--argName', '--argName=Value', 'Value')
      testcase('-arg', '-arg="-DSanitizerMode=ON"', '"-DSanitizerMode=ON"')

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(ArgParserTests, testNames)
