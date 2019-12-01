#include "pch.h"

TESTS(RandomGeneratorTests)
AFACT(AllRandomGeneratorFunctions_ReturnsRandomValues)
EVIDENCE

TEST(AllRandomGeneratorFunctions_ReturnsRandomValues)
{
   const RandomGenerator randomGenerator;

   const char randomChar = randomGenerator.Char();
   const unsigned char randomUnsignedChar = randomGenerator.UnsignedChar();

   const bool randomBool = randomGenerator.Bool();

   const short randomShort = randomGenerator.Short();
   const unsigned short randomUnsignedShort = randomGenerator.UnsignedShort();

   const int randomInt = randomGenerator.Int();
   const unsigned int randomUnsignedInt = randomGenerator.UnsignedInt();

   const int randomEnumIntValue = randomGenerator.Enum(0);

   const long long randomLongLong = randomGenerator.LongLong();
   const unsigned long long randomUnsignedLongLong = randomGenerator.UnsignedLongLong();
   const size_t randomSizeT = randomGenerator.SizeT();

   const float randomFloat = randomGenerator.Float();
   const double randomDouble = randomGenerator.Double();

   const char* const randomConstCharPointer = randomGenerator.ConstCharPointer();
   POINTER_IS_NOT_NULL(randomConstCharPointer);

   const string randomString = randomGenerator.String();

   const vector<string> randomStringVector = randomGenerator.StringVector();

   const fs::path randomPath = randomGenerator.Path();

   const error_code randomErrorCode = randomGenerator.ErrorCode();
}

RUN_TESTS(RandomGeneratorTests)
