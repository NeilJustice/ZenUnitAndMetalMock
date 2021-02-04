import random

def boolean():
   randomInteger = integer()
   randomBoolean = randomInteger % 2 == 0
   return randomBoolean

def integer():
   randomInteger = random.randint(-10000, 10000)
   return randomInteger

def float_value():
   randomFloat = random.uniform(-10000, 10000)
   return randomFloat

def string():
   randomString = 'RandomString' + str(random.randint(0, 10000))
   return randomString
