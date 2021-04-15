import random

def boolean() -> bool:
   randomInteger = integer()
   randomBoolean = randomInteger % 2 == 0
   return randomBoolean

def integer() -> int:
   randomInteger = random.randint(-10000, 10000)
   return randomInteger

def string() -> str:
   randomString = 'RandomString' + str(random.randint(0, 10000))
   return randomString
