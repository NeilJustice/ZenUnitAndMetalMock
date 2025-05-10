#include "pch.h"

namespace ZenUnit
{
   TESTS(RandomGeneratorTests)
   AFACT(RandomEngineForCurrentTestRun_randomEngineForCurrentTestRunIsNotNullptr_ReturnsRandomEngineForCurrentTestRun)
   AFACT(RandomEngineForCurrentTestRun_randomEngineForCurrentTestRunIsNullptr_SetsNewRandomEngineForNewTestRun_ReturnsRandomEngineForCurrentTestRun)
   AFACT(AllRandomGeneratorFunctions_ReturnsRandomValues)
   AFACT(Enum_ReturnsIntBetween0InclusiveAndEnumMaxValueExclusive)
   AFACT(RandomSizeTBetween_CodeCoverageOfAllBranches)
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
      [[maybe_unused]] const char randomChar = _randomGenerator.Char();
      [[maybe_unused]] const char randomCharBetween = _randomGenerator.CharBetween('A', 'Z');
      [[maybe_unused]] const char randomLetter = _randomGenerator.Letter();
      [[maybe_unused]] const unsigned char randomUnsignedChar = _randomGenerator.UnsignedChar();
      [[maybe_unused]] const bool randomBool = _randomGenerator.Bool();
      [[maybe_unused]] const short randomShort = _randomGenerator.Short();
      [[maybe_unused]] const unsigned short randomUnsignedShort = _randomGenerator.UnsignedShort();
      [[maybe_unused]] const int randomInt = _randomGenerator.Int();

      const int randomIntBetween1And3 = _randomGenerator.IntBetween(1, 3);
      IS_TRUE(randomIntBetween1And3 >= 1 && randomIntBetween1And3 <= 3);

      const int randomIntBetween5And7 = _randomGenerator.IntBetween(5, 7);
      IS_TRUE(randomIntBetween5And7 >= 5 && randomIntBetween5And7 <= 7);

      [[maybe_unused]] const unsigned randomUnsigned = _randomGenerator.Unsigned();
      [[maybe_unused]] const vector<unsigned> randomUnsignedVector = _randomGenerator.UnsignedVector();

      [[maybe_unused]] const int randomEnumIntValue = _randomGenerator.Enum(1);

      [[maybe_unused]] const long long randomLongLong = _randomGenerator.LongLong();

      [[maybe_unused]] const unsigned long long randomUnsignedLongLong = _randomGenerator.UnsignedLongLong();

      [[maybe_unused]] const size_t randomSizeT = _randomGenerator.SizeT();

      const size_t randomSizeTBetween1And3 = _randomGenerator.SizeTBetween(1, 3);
      IS_TRUE(randomSizeTBetween1And3 >= 1 && randomSizeTBetween1And3 <= 3);

      const size_t randomSizeTBetween5And7 = _randomGenerator.SizeTBetween(5, 7);
      IS_TRUE(randomSizeTBetween5And7 >= 5 && randomSizeTBetween1And3 <= 7);

      const size_t randomSizeTBetweenLongLongMaxPlus1AndSizeTMax = _randomGenerator.SizeTBetween(static_cast<size_t>(numeric_limits<long long>::max()) + 1, numeric_limits<size_t>::max());
      IS_TRUE(randomSizeTBetweenLongLongMaxPlus1AndSizeTMax >= static_cast<size_t>(numeric_limits<long long>::max()) + 1 && randomSizeTBetweenLongLongMaxPlus1AndSizeTMax <= numeric_limits<size_t>::max());

      [[maybe_unused]] const float randomFloat = _randomGenerator.Float();

      const float randomFloatBetween = _randomGenerator.FloatBetween(-3.0f, 3.0f);
      IS_GREATER_THAN_OR_EQUAL(randomFloatBetween, -3.0f);
      IS_LESS_THAN_OR_EQUAL(randomFloatBetween, 3.0f);

      [[maybe_unused]] const vector<float> randomFloatVector = _randomGenerator.FloatVector();

      [[maybe_unused]] const double randomDouble = _randomGenerator.Double();

      const double randomDoubleBetween = _randomGenerator.DoubleBetween(-3.0, 3.0);
      IS_GREATER_THAN_OR_EQUAL(randomDoubleBetween, -3.0);
      IS_LESS_THAN_OR_EQUAL(randomDoubleBetween, 3.0);

      [[maybe_unused]] const vector<double> randomDoubleVector = _randomGenerator.DoubleVector();

      const char* const randomConstCharPointer = _randomGenerator.ConstCharPointer();
      IS_NOT_NULLPTR(randomConstCharPointer);

      [[maybe_unused]] const string randomString = _randomGenerator.String();

      [[maybe_unused]] const string_view randomStringView = _randomGenerator.StringView();

      [[maybe_unused]] const vector<string> randomStringVector = _randomGenerator.StringVector();

      [[maybe_unused]] const error_code randomErrorCode = _randomGenerator.ErrorCode();

      [[maybe_unused]] const std::filesystem::path randomFilesystemPath = _randomGenerator.FilesystemPath();

      const vector<fs::path> randomFilesystemPathVector = _randomGenerator.FilesystemPathVector();
      IS_TRUE(randomFilesystemPathVector.size() <= 3);

      const shared_ptr<vector<char>> randomSharedPtrToCharsVector = _randomGenerator.SharedPtrToCharsVector();
      IS_NOT_NULLPTR(randomSharedPtrToCharsVector);
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

   TEST(RandomSizeTBetween_CodeCoverageOfAllBranches)
   {
      const RandomGenerator* const randomGenerator = RandomGenerator::Instance();
      //
      for (size_t i = 0; i < 500; ++i)
      {
         const size_t randomSizeTBetween = randomGenerator->SizeTBetween(5, 10);
         IS_TRUE(randomSizeTBetween >= 5 && randomSizeTBetween <= 10);
      }
   }

   RUN_TESTS(RandomGeneratorTests)
}
