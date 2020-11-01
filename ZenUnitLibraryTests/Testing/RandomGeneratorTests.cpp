#include "pch.h"

TESTS(RandomGeneratorTests)
AFACT(AllRandomGeneratorFunctions_ReturnsRandomValues)
EVIDENCE

TEST(AllRandomGeneratorFunctions_ReturnsRandomValues)
{
   const RandomGenerator* randomGenerator = RandomGenerator::Instance();

   const char randomChar = randomGenerator->Char();
   ARE_EQUAL(randomChar, randomChar);

   const unsigned char randomUnsignedChar = randomGenerator->UnsignedChar();
   ARE_EQUAL(randomUnsignedChar, randomUnsignedChar);

   const bool randomBool = randomGenerator->Bool();
   ARE_EQUAL(randomBool, randomBool);

   const short randomShort = randomGenerator->Short();
   ARE_EQUAL(randomShort, randomShort);

   const unsigned short randomUnsignedShort = randomGenerator->UnsignedShort();
   ARE_EQUAL(randomUnsignedShort, randomUnsignedShort);

   const int randomInt = randomGenerator->Int();
   ARE_EQUAL(randomInt, randomInt);

   const unsigned int randomUnsignedInt = randomGenerator->UnsignedInt();
   ARE_EQUAL(randomUnsignedInt, randomUnsignedInt);

   const int randomEnumIntValue = randomGenerator->Enum(0);
   ARE_EQUAL(randomEnumIntValue, randomEnumIntValue);

   const long long randomLongLong = randomGenerator->LongLong();
   ARE_EQUAL(randomLongLong, randomLongLong);

   const unsigned long long randomUnsignedLongLong = randomGenerator->UnsignedLongLong();
   ARE_EQUAL(randomUnsignedLongLong, randomUnsignedLongLong);

   const size_t randomSizeT = randomGenerator->SizeT();
   ARE_EQUAL(randomSizeT, randomSizeT);

   const float randomFloat = randomGenerator->Float();
   ARE_EQUAL(randomFloat, randomFloat);

   const double randomDouble = randomGenerator->Double();
   ARE_EQUAL(randomDouble, randomDouble);

   const char* const randomConstCharPointer = randomGenerator->ConstCharPointer();
   ARE_EQUAL(randomConstCharPointer, randomConstCharPointer);

   IS_NOT_NULLPTR(randomConstCharPointer);

   const string randomString = randomGenerator->String();
   ARE_EQUAL(randomString, randomString);

   const vector<string> randomStringVector = randomGenerator->StringVector();
   ARE_EQUAL(randomStringVector, randomStringVector);

   const fs::path randomFilesystemPath = randomGenerator->FilesystemPath();
   ARE_EQUAL(randomFilesystemPath, randomFilesystemPath);

   const error_code randomErrorCode = randomGenerator->ErrorCode();
   ARE_EQUAL(randomErrorCode, randomErrorCode);
}

RUN_TESTS(RandomGeneratorTests)
