#include "pch.h"

namespace ZenUnit
{
   TESTS(RandomGeneratorTests)
   AFACT(RandomEngineForCurrentTestRun_randomEngineForCurrentTestRunIsNotNullptr_ReturnsRandomEngineForCurrentTestRun)
   AFACT(RandomEngineForCurrentTestRun_randomEngineForCurrentTestRunIsNullptr_SetsNewRandomEngineForNewTestRun_ReturnsRandomEngineForCurrentTestRun)
   AFACT(AllRandomGeneratorFunctions_ReturnsRandomValues)
   AFACT(Enum_ReturnsIntBetween0InclusiveAndEnumMaxValueExclusive)
   EVIDENCE

   RandomGenerator _randomGenerator;

   TEST(RandomEngineForCurrentTestRun_randomEngineForCurrentTestRunIsNotNullptr_ReturnsRandomEngineForCurrentTestRun)
   {
      std::default_random_engine& defaultRandomEngine = ZenUnit::RandomEngineForCurrentTestRun();
      //
      defaultRandomEngine.discard(0);
   }

   TEST(RandomEngineForCurrentTestRun_randomEngineForCurrentTestRunIsNullptr_SetsNewRandomEngineForNewTestRun_ReturnsRandomEngineForCurrentTestRun)
   {
      ZenUnit::globalZenUnitMode.randomEngineForCurrentTestRun.reset();
      //
      std::default_random_engine& defaultRandomEngine = ZenUnit::RandomEngineForCurrentTestRun();
      //
      defaultRandomEngine.discard(0);
   }

   TEST(AllRandomGeneratorFunctions_ReturnsRandomValues)
   {
      const char randomChar = _randomGenerator.Char();
      ARE_EQUAL(randomChar, randomChar);

      const unsigned char randomUnsignedChar = _randomGenerator.UnsignedChar();
      ARE_EQUAL(randomUnsignedChar, randomUnsignedChar);

      const bool randomBool = _randomGenerator.Bool();
      ARE_EQUAL(randomBool, randomBool);

      const short randomShort = _randomGenerator.Short();
      ARE_EQUAL(randomShort, randomShort);

      const unsigned short randomUnsignedShort = _randomGenerator.UnsignedShort();
      ARE_EQUAL(randomUnsignedShort, randomUnsignedShort);

      const int randomInt = _randomGenerator.Int();
      ARE_EQUAL(randomInt, randomInt);

      const unsigned int randomUnsignedInt = _randomGenerator.UnsignedInt();
      ARE_EQUAL(randomUnsignedInt, randomUnsignedInt);

      const int randomEnumIntValue = _randomGenerator.Enum(1);
      IS_ZERO(randomEnumIntValue);

      const long long randomLongLong = _randomGenerator.LongLong();
      ARE_EQUAL(randomLongLong, randomLongLong);

      const unsigned long long randomUnsignedLongLong = _randomGenerator.UnsignedLongLong();
      ARE_EQUAL(randomUnsignedLongLong, randomUnsignedLongLong);

      const size_t randomSizeT = _randomGenerator.SizeT();
      ARE_EQUAL(randomSizeT, randomSizeT);

      const size_t randomSizeTBetween1And3 = _randomGenerator.SizeTBetween(1, 3);
      IS_TRUE(randomSizeTBetween1And3 >= 1 && randomSizeTBetween1And3 <= 3);
      const size_t randomSizeTBetween5And7 = _randomGenerator.SizeTBetween(5, 7);
      IS_TRUE(randomSizeTBetween5And7 >= 5 && randomSizeTBetween1And3 <= 7);
      const size_t randomSizeTBetweenLongLongMaxPlus1AndSizeTMax = _randomGenerator.SizeTBetween(static_cast<size_t>(numeric_limits<long long>::max()) + 1, numeric_limits<size_t>::max());
      IS_TRUE(randomSizeTBetweenLongLongMaxPlus1AndSizeTMax >= static_cast<size_t>(numeric_limits<long long>::max()) + 1 && randomSizeTBetweenLongLongMaxPlus1AndSizeTMax <= numeric_limits<size_t>::max());

      const float randomFloat = _randomGenerator.Float();
      ARE_EQUAL(randomFloat, randomFloat);

      const float randomFloatBetween = _randomGenerator.FloatBetween(-3.0f, 3.0f);
      IS_GREATER_THAN_OR_EQUAL(randomFloatBetween, -3.0f);
      IS_LESS_THAN_OR_EQUAL(randomFloatBetween, 3.0f);

      const vector<float> randomFloatVector = _randomGenerator.FloatVector();
      ARE_EQUAL(randomFloatVector, randomFloatVector);

      const double randomDouble = _randomGenerator.Double();
      ARE_EQUAL(randomDouble, randomDouble);

      const double randomDoubleBetween = _randomGenerator.DoubleBetween(-3.0, 3.0);
      IS_GREATER_THAN_OR_EQUAL(randomDoubleBetween, -3.0);
      IS_LESS_THAN_OR_EQUAL(randomDoubleBetween, 3.0);

      const vector<double> randomDoubleVector = _randomGenerator.DoubleVector();
      ARE_EQUAL(randomDoubleVector, randomDoubleVector);

      const char* const randomConstCharPointer = _randomGenerator.ConstCharPointer();
      ARE_EQUAL(randomConstCharPointer, randomConstCharPointer);
      IS_NOT_NULLPTR(randomConstCharPointer);

      const string randomString = _randomGenerator.String();
      ARE_EQUAL(randomString, randomString);

      const vector<string> randomStringVector = _randomGenerator.StringVector();
      ARE_EQUAL(randomStringVector, randomStringVector);

      const error_code randomErrorCode = _randomGenerator.ErrorCode();
      ARE_EQUAL(randomErrorCode, randomErrorCode);

      const std::filesystem::path randomFilesystemPath = _randomGenerator.FilesystemPath();
      ARE_EQUAL(randomFilesystemPath, randomFilesystemPath);

      const std::vector<std::filesystem::path> randomFilesystemPathVector = _randomGenerator.FilesystemPathVector();
      IS_TRUE(randomFilesystemPathVector.size() <= 3);

      const vector<int> randomVectorOfTBetweenSize0And3 = _randomGenerator.Vector<int>();
      IS_TRUE(randomVectorOfTBetweenSize0And3.size() <= 3);

      const vector<int> randomVectorOfTBetweenSize1And3 = _randomGenerator.NonEmptyVector<int>();
      IS_TRUE(randomVectorOfTBetweenSize1And3.size() <= 3);

      _randomGenerator.StdArray<int, 3>();

      const unordered_map<int, string> randomUnorderedMap = _randomGenerator.UnorderedMap<int, string>();
      IS_TRUE(randomUnorderedMap.size() <= 3);
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
