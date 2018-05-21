import random

def integer():
   randomInteger = random.randint(-100, 100)
   return randomInteger

def string():
   randomString = 'RandomString' + str(random.randint(0, 100))
   return randomString
