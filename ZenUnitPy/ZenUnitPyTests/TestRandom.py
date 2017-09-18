import random

def integer():
   randomInteger = random.randint(-100, 100)
   return randomInteger

def string():
   randomString = 'RandomString' + str(integer())
   return randomString
