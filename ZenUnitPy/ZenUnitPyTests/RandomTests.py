import re
import unittest
from ZenUnitPy import UnitTester, Random

testNames = [
'boolean_RandomsRandomBoolean_test',
'integer_RandomsRandomIntegerBetweenNegative10000And10000_test',
'float_value_RandomsRandomFloatBetweenNegative10000And10000_test',
'string_ReturnsTextRandomStringFollowedRandomIntBetween0And10000_test'
]

class RandomTests(unittest.TestCase):

   def boolean_RandomsRandomBoolean_test(self):
      randomBoolean = Random.boolean()
      self.assertTrue(randomBoolean is True or randomBoolean is False)

   def integer_RandomsRandomIntegerBetweenNegative10000And10000_test(self):
      randomInteger = Random.integer()
      self.assertTrue(-10000 <= randomInteger <= 10000)

   def float_value_RandomsRandomFloatBetweenNegative10000And10000_test(self):
      randomFloat = Random.float_value()
      self.assertTrue(-10000 <= randomFloat <= 10000)

   def string_ReturnsTextRandomStringFollowedRandomIntBetween0And10000_test(self):
      randomString = Random.string()
      self.assertTrue(re.fullmatch(r'RandomString\d{1,4}', randomString))

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(RandomTests, testNames)
