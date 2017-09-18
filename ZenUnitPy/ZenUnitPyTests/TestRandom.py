import random

def integer():
   randomInteger = random.randrange(-100, 100, 1)
   return randomInteger

def string():
   randomString = 'RandomString' + str(integer())
   return randomString
