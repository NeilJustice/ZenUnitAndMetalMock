#include "pch.h"

namespace ZenUnit
{
   TESTS(RandomGeneratorTests)
   AFACT(AllRandomGeneratorFunctions_ReturnsRandomValues)
   AFACT(Enum_ReturnsIntBetween0InclusiveAndEnumMaxValueExclusive)
   EVIDENCE

   TEST(AllRandomGeneratorFunctions_ReturnsRandomValues)
   {
      const RandomGenerator* const randomGenerator = RandomGenerator::Instance();

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

      const int randomEnumIntValue = randomGenerator->Enum(1);
      IS_ZERO(randomEnumIntValue);

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

   enum TestEnum
   {
      A,
      B,
      C,
      MaxValue
   };

   TEST(Enum_ReturnsIntBetween0InclusiveAndEnumMaxValueExclusive)
   {
      const RandomGenerator* const randomGenerator = RandomGenerator::Instance();
      bool didSee0 = false;
      bool didSee1 = false;
      bool didSee2 = false;
      for (size_t i = 0; i < 100; ++i)
      {
         const int randomEnumInt = randomGenerator->Enum(TestEnum::MaxValue);
         if (randomEnumInt == 0)
         {
            didSee0 = true;
         }
         else if (randomEnumInt == 1)
         {
            didSee1 = true;
         }
         else if (randomEnumInt == 2)
         {
            didSee2 = true;
         }
         else
         {
            FAIL_TEST("randomGenerator->Enum(TestEnum::MaxValue) did not return 0, 1, or 2"); // LCOV_EXCL_LINE
         }
         if (didSee0 && didSee1 && didSee2)
         {
            break;
         }
      }
      IS_TRUE(didSee0);
      IS_TRUE(didSee1);
      IS_TRUE(didSee2);
   }

   RUN_TESTS(RandomGeneratorTests)
}
