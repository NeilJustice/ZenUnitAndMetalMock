import re
import unittest
from ZenUnitPy import UnitTester, Random

testNames = [
'test_boolean_RandomsRandomBoolean',
'test_integer_RandomsRandomIntegerBetweenNegative10000And10000',
'test_string_ReturnsTextRandomStringFollowedRandomIntBetween0And10000'
]

class RandomTests(unittest.TestCase):

   def test_boolean_RandomsRandomBoolean(self):
      randomBoolean = Random.boolean()
      self.assertTrue(randomBoolean is True or randomBoolean is False)

   def test_integer_RandomsRandomIntegerBetweenNegative10000And10000(self):
      randomInteger = Random.integer()
      self.assertTrue(-10000 <= randomInteger <= 10000)

   def test_string_ReturnsTextRandomStringFollowedRandomIntBetween0And10000(self):
      randomString = Random.string()
      self.assertTrue(re.fullmatch(r'RandomString\d{1,4}', randomString))

if __name__ == '__main__': # pragma nocover
   UnitTester.run_tests(RandomTests, testNames)
