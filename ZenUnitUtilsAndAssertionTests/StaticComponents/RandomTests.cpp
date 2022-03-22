#include "pch.h"
#include "ZenUnitUtilsAndAssertionTests/Assertions/REGEX_MATCHES.h"

namespace ZenUnit
{
   TESTS(RandomTests)
   AFACT(Random_AllIntegerTypes_ReturnsRandomValueBetweenMinAndMaxForThatType)
   AFACT(Random_TIsEnum_ReturnsRandomEnumBetween0AndEnumMaxValue)
   AFACT(Random_TIsAPair_ReturnsRandomPair)
   AFACT(Random_TIsAVector_ReturnsRandomVectorOfTWithSizeLessThanOrEqualTo3)
   AFACT(Random_TIsAnUnorderedMap_ReturnsRandomUnorderedMap)
   AFACT(Random_TIsAnUnorderedSet_ReturnsRandomUnorderedSet)
   AFACT(RandomNon0_ReturnsNon0RandomValueBetweenMinAndMaxForTypeT)
   AFACT(RandomNon0_TIsEnum_ReturnsRandomEnumBetween1AndEnumMaxValue)
   AFACT(RandomNotEqualTo_ReturnsRandomValueBetweenMinAndMaxForTypeTNotEqualToTheExceptValue)
   AFACT(RandomNon0NotEqualTo_NotEqualValueIs0_ThrowsInvalidArgument)
   AFACT(RandomNon0NotEqualTo_ReturnsRandomValueBetweenMinAndMaxForTypeTNotEqualTo0AndNotEqualToTheExceptValue)
   AFACT(RandomEnumNotEqualTo_ReturnsEnumBetween0AndEnumMaxValueThatIsNotEqualToNotEqualEnum__EnumTypeOneValueTestCase)
   AFACT(RandomEnumNotEqualTo_ReturnsEnumBetween0AndEnumMaxValueThatIsNotEqualToNotEqualEnum__EnumTypeTwoValueTestCase)
   AFACT(Random_Float_ReturnsRandomFloat)
   AFACT(Random_Double_ReturnsRandomDouble)
   AFACT(Random_ConstCharPointer_ReturnsRandomConstCharPointer1Through10)
   AFACT(Random_ConstWCharTPointer_CodeCoverage)
   AFACT(Random_FilesystemPath_ReturnsFilesystemPathWithBetween0And2Subfolders)
   AFACT(Random_ErrorCode_ReturnsEitherGenericCategoryOrIostreamCategoryOrSystemCategoryErrorCode)
   AFACT(Random_String_ReturnsRandomString1Through10)
   AFACT(Random_WideString_CodeCoverage)
   AFACT(RandomLetter_ReturnsUppercaseAThroughZ50PercentOfTheTime_ReturnsLowercaseAThroughZ50PercentOfTheTime)
   AFACT(RandomWideLetter_ReturnsUppercaseAThroughZ50PercentOfTheTime_ReturnsLowercaseAThroughZ50PercentOfTheTime)
   AFACT(RandomStringWithLength_ReturnsRandomStringWithLength)
   AFACT(RandomWideStringWithLength_ReturnsRandomWideStringWithLength)
   AFACT(RandomBetween_ReturnsRandomValueBetweenInclusiveLowerBoundAndInclusiveUpperBound)
   AFACT(RandomSizeTBetween_InclusiveLowerBoundEqualsInclusiveUpperBound_ReturnsInclusiveLowerBound)
   AFACT(RandomSizeTBetween_ReturnsRandomValueBetweenInclusiveLowerBoundAndInclusiveUpperBound)
   AFACT(RandomFloatBetween_ReturnsRandomFloatBetweenInclusiveLowerBoundAndInclusiveUpperBound)
   AFACT(RandomDoubleBetween_ReturnsRandomDoubleBetweenInclusiveLowerBoundAndInclusiveUpperBound)
   AFACT(RandomUnsignedLongLong_ReturnsRandomUnsignedLongLongBetween0AndUnsignedLongLongMaxValue)
   FACTS(RandomUnsignedLongLongBetween0AndValue_ReturnsRandomUnsignedLongLongBetween0AndInclusiveMaxValue)
   EVIDENCE

   enum struct EnumType
   {
      ZeroValue,
      OneValue,
      TwoValue,
      MaxValue
   };

   TEST(Random_AllIntegerTypes_ReturnsRandomValueBetweenMinAndMaxForThatType)
   {
      Random<char>();
      Random<unsigned char>();
      Random<short>();
      Random<unsigned short>();
      Random<int>();
      Random<unsigned int>();
      Random<long long>();
      Random<unsigned long long>();
      Random<size_t>();
   }

   TEST(Random_TIsEnum_ReturnsRandomEnumBetween0AndEnumMaxValue)
   {
      set<EnumType> randomEnumsReturned;
      for (size_t i = 0; i < 1000; ++i)
      {
         const EnumType randomEnum = Random<EnumType>();
         randomEnumsReturned.insert(randomEnum);
      }
      const set<EnumType> expectedRandomEnumsReturned
      {
         EnumType::ZeroValue,
         EnumType::OneValue,
         EnumType::TwoValue
      };
      SETS_ARE_EQUAL(expectedRandomEnumsReturned, randomEnumsReturned);
   }

   TEST(Random_TIsAPair_ReturnsRandomPair)
   {
      [[maybe_unused]]
      const pair<int, string> randomIntStringPair = Random<pair<int, string>>();

      [[maybe_unused]]
      const pair<double, char> randomDoubleCharPair = Random<pair<double, char>>();
   }

   TEST(Random_TIsAVector_ReturnsRandomVectorOfTWithSizeLessThanOrEqualTo3)
   {
      const vector<int> randomIntVector = Random<vector<int>>();
      IS_TRUE(randomIntVector.size() <= 3);

      const vector<string> randomStringVector = Random<vector<string>>();
      IS_TRUE(randomStringVector.size() <= 3);
   }

   TEST(Random_TIsAnUnorderedMap_ReturnsRandomUnorderedMap)
   {
      [[maybe_unused]]
      const unordered_map<int, int> intIntUnorderedMap = Random<unordered_map<int, int>>();

      [[maybe_unused]]
      const unordered_map<string, double> stringDoubleUnorderedMap = Random<unordered_map<string, double>>();
   }

   TEST(Random_TIsAnUnorderedSet_ReturnsRandomUnorderedSet)
   {
      [[maybe_unused]]
      const unordered_set<int> unorderedIntSet = Random<unordered_set<int>>();

      [[maybe_unused]]
      const unordered_set<string> unorderedStringSet = Random<unordered_set<string>>();
   }

   TEST(RandomNon0_ReturnsNon0RandomValueBetweenMinAndMaxForTypeT)
   {
      ARE_NOT_EQUAL(0, RandomNon0<char>());
      ARE_NOT_EQUAL(0, RandomNon0<unsigned char>());
      ARE_NOT_EQUAL(0, RandomNon0<short>());
      ARE_NOT_EQUAL(0, RandomNon0<unsigned short>());
      ARE_NOT_EQUAL(0, RandomNon0<int>());
      ARE_NOT_EQUAL(0, RandomNon0<unsigned int>());
      ARE_NOT_EQUAL(0, RandomNon0<long long>());
      ARE_NOT_EQUAL(0, RandomNon0<unsigned long long>());
   }

   TEST(RandomNon0_TIsEnum_ReturnsRandomEnumBetween1AndEnumMaxValue)
   {
      unordered_set<EnumType> randomEnumsReturned;
      for (size_t i = 0; i < 1000; ++i)
      {
         const EnumType randomNon0Enum = RandomNon0<EnumType>();
         randomEnumsReturned.insert(randomNon0Enum);
      }
      const unordered_set<EnumType> expectedRandomEnumsReturned
      {
         EnumType::OneValue,
         EnumType::TwoValue
      };
      SETS_ARE_EQUAL(expectedRandomEnumsReturned, randomEnumsReturned);
   }

   TEST(RandomNotEqualTo_ReturnsRandomValueBetweenMinAndMaxForTypeTNotEqualToTheExceptValue)
   {
      const char char1 = ZenUnit::Random<char>();
      const char char2 = ZenUnit::RandomNotEqualTo<char>(char1);
      ARE_NOT_EQUAL(char1, char2);

      const unsigned char unsignedChar1 = ZenUnit::Random<unsigned char>();
      const unsigned char unsignedChar2 = ZenUnit::RandomNotEqualTo<unsigned char>(unsignedChar1);
      ARE_NOT_EQUAL(unsignedChar1, unsignedChar2);

      const short short1 = ZenUnit::Random<short>();
      const short short2 = ZenUnit::RandomNotEqualTo<short>(short1);
      ARE_NOT_EQUAL(short1, short2);

      const unsigned short unsignedShort1 = ZenUnit::Random<unsigned short>();
      const unsigned short unsignedShort2 = ZenUnit::RandomNotEqualTo<unsigned short>(unsignedShort1);
      ARE_NOT_EQUAL(unsignedShort1, unsignedShort2);

      const int int1 = ZenUnit::Random<int>();
      const int int2 = ZenUnit::RandomNotEqualTo<int>(int1);
      ARE_NOT_EQUAL(int1, int2);

      const unsigned unsigned1 = ZenUnit::Random<unsigned>();
      const unsigned unsigned2 = ZenUnit::RandomNotEqualTo<unsigned>(unsigned1);
      ARE_NOT_EQUAL(unsigned1, unsigned2);

      const long long longLong1 = ZenUnit::Random<long long>();
      const long long longLong2 = ZenUnit::RandomNotEqualTo<long long>(longLong1);
      ARE_NOT_EQUAL(longLong1, longLong2);

      const unsigned long long unsignedLongLong1 = ZenUnit::Random<unsigned long long>();
      const unsigned long long unsignedLongLong2 = ZenUnit::RandomNotEqualTo<unsigned long long>(unsignedLongLong1);
      ARE_NOT_EQUAL(unsignedLongLong1, unsignedLongLong2);
   }

   TEST(RandomNon0NotEqualTo_NotEqualValueIs0_ThrowsInvalidArgument)
   {
      THROWS_EXCEPTION(ZenUnit::RandomNon0NotEqualTo<int>(0),
         invalid_argument, "ZenUnit::RandomNon0NotEqualTo<T>(const T& notEqualValue) called with notEqualValue == T{0}");
      THROWS_EXCEPTION(ZenUnit::RandomNon0NotEqualTo<double>(0.0),
         invalid_argument, "ZenUnit::RandomNon0NotEqualTo<T>(const T& notEqualValue) called with notEqualValue == T{0}");
   }

   TEST(RandomNon0NotEqualTo_ReturnsRandomValueBetweenMinAndMaxForTypeTNotEqualTo0AndNotEqualToTheExceptValue)
   {
      const char char1 = ZenUnit::RandomNon0<char>();
      const char char2 = ZenUnit::RandomNon0NotEqualTo<char>(char1);
      ARE_NOT_EQUAL(0, char2);
      ARE_NOT_EQUAL(char1, char2);

      const unsigned char unsignedChar1 = ZenUnit::RandomNon0<unsigned char>();
      const unsigned char unsignedChar2 = ZenUnit::RandomNon0NotEqualTo<unsigned char>(unsignedChar1);
      ARE_NOT_EQUAL(0, unsignedChar2);
      ARE_NOT_EQUAL(unsignedChar1, unsignedChar2);

      const short short1 = ZenUnit::RandomNon0<short>();
      const short short2 = ZenUnit::RandomNon0NotEqualTo<short>(short1);
      ARE_NOT_EQUAL(0, short2);
      ARE_NOT_EQUAL(short1, short2);

      const unsigned short unsignedShort1 = ZenUnit::RandomNon0<unsigned short>();
      const unsigned short unsignedShort2 = ZenUnit::RandomNon0NotEqualTo<unsigned short>(unsignedShort1);
      ARE_NOT_EQUAL(0, unsignedShort2);
      ARE_NOT_EQUAL(unsignedShort1, unsignedShort2);

      const int int1 = ZenUnit::RandomNon0<int>();
      const int int2 = ZenUnit::RandomNon0NotEqualTo<int>(int1);
      ARE_NOT_EQUAL(0, int2);
      ARE_NOT_EQUAL(int1, int2);

      const unsigned int unsigned1 = ZenUnit::RandomNon0<unsigned>();
      const unsigned int unsigned2 = ZenUnit::RandomNon0NotEqualTo<unsigned>(unsigned1);
      ARE_NOT_EQUAL(0, unsigned2);
      ARE_NOT_EQUAL(unsigned1, unsigned2);

      const long long longLong1 = ZenUnit::RandomNon0<long long>();
      const long long longLong2 = ZenUnit::RandomNon0NotEqualTo<long long>(longLong1);
      ARE_NOT_EQUAL(0, longLong2);
      ARE_NOT_EQUAL(longLong1, longLong2);

      const unsigned long long unsignedLongLong1 = ZenUnit::RandomNon0<unsigned long long>();
      const unsigned long long unsignedLongLong2 = ZenUnit::RandomNon0NotEqualTo<unsigned long long>(unsignedLongLong1);
      ARE_NOT_EQUAL(0, unsignedLongLong2);
      ARE_NOT_EQUAL(unsignedLongLong1, unsignedLongLong2);

      // Code coverage for the while-loop body in RandomNon0NotEqualTo
      for (size_t i = 0; i < 100; ++i)
      {
         const int returnValue = ZenUnit::RandomNon0NotEqualTo<int>(INT_MAX);
         ARE_NOT_EQUAL(INT_MAX, returnValue);
      }
   }

   TEST(RandomEnumNotEqualTo_ReturnsEnumBetween0AndEnumMaxValueThatIsNotEqualToNotEqualEnum__EnumTypeOneValueTestCase)
   {
      unordered_set<EnumType> randomEnumsReturned;
      for (size_t i = 0; i < 1000; ++i)
      {
         const EnumType randomEnum = ZenUnit::RandomEnumNotEqualTo<EnumType>(EnumType::OneValue, EnumType::MaxValue);
         randomEnumsReturned.insert(randomEnum);
      }
      const unordered_set<EnumType> expectedRandomEnumsReturned
      {
         EnumType::ZeroValue,
         EnumType::TwoValue
      };
      SETS_ARE_EQUAL(expectedRandomEnumsReturned, randomEnumsReturned);
   }

   TEST(RandomEnumNotEqualTo_ReturnsEnumBetween0AndEnumMaxValueThatIsNotEqualToNotEqualEnum__EnumTypeTwoValueTestCase)
   {
      unordered_set<EnumType> randomEnumsReturned;
      for (size_t i = 0; i < 1000; ++i)
      {
         const EnumType randomEnum = ZenUnit::RandomEnumNotEqualTo<EnumType>(EnumType::TwoValue, EnumType::MaxValue);
         randomEnumsReturned.insert(randomEnum);
      }
      const unordered_set<EnumType> expectedRandomEnumsReturned
      {
         EnumType::ZeroValue,
         EnumType::OneValue
      };
      SETS_ARE_EQUAL(expectedRandomEnumsReturned, randomEnumsReturned);
   }

   TEST(Random_Float_ReturnsRandomFloat)
   {
      bool didReturnLowestFloatValue = false;
      bool didReturnValueBetweenFloatMinValueAnd0 = false;
      bool didReturnFloat0 = false;
      bool didReturnValueBetweenFloat0AndFloatMaxValue = false;
      bool didReturnMaxFloatValue = false;
      //
      for (size_t i = 0; i < 10000; ++i)
      {
         const float randomFloat = Random<float>();
         if (randomFloat == std::numeric_limits<float>::lowest())
         {
            didReturnLowestFloatValue = true;
         }
         else if (randomFloat == 0.0f)
         {
            didReturnFloat0 = true;
         }
         else if (randomFloat == FLT_MAX)
         {
            didReturnMaxFloatValue = true;
         }
         else if (randomFloat < 0.0f)
         {
            didReturnValueBetweenFloatMinValueAnd0 = true;
         }
         else
         {
            didReturnValueBetweenFloat0AndFloatMaxValue = true;
         }
         if (didReturnLowestFloatValue &&
             didReturnValueBetweenFloatMinValueAnd0 &&
             didReturnFloat0 &&
             didReturnValueBetweenFloat0AndFloatMaxValue &&
             didReturnMaxFloatValue)
         {
            break;
         }
      }
      //
      IS_TRUE(didReturnLowestFloatValue);
      IS_TRUE(didReturnValueBetweenFloatMinValueAnd0);
      IS_TRUE(didReturnFloat0);
      IS_TRUE(didReturnValueBetweenFloat0AndFloatMaxValue);
      IS_TRUE(didReturnMaxFloatValue);
   }

   TEST(Random_Double_ReturnsRandomDouble)
   {
      bool didReturnLowestDoubleValue = false;
      bool didReturnValueBetweenDoubleMinValueAnd0 = false;
      bool didReturnDouble0 = false;
      bool didReturnValueBetweenDouble0AndDoubleMaxValue = false;
      bool didReturnMaxDoubleValue = false;
      //
      for (size_t i = 0; i < 10000; ++i)
      {
         const double randomDouble = Random<double>();
         if (randomDouble == std::numeric_limits<double>::lowest())
         {
            didReturnLowestDoubleValue = true;
         }
         else if (randomDouble == 0.0)
         {
            didReturnDouble0 = true;
         }
         else if (randomDouble == DBL_MAX)
         {
            didReturnMaxDoubleValue = true;
         }
         else if (randomDouble < 0.0)
         {
            didReturnValueBetweenDoubleMinValueAnd0 = true;
         }
         else
         {
            didReturnValueBetweenDouble0AndDoubleMaxValue = true;
         }
         if (didReturnLowestDoubleValue &&
             didReturnValueBetweenDoubleMinValueAnd0 &&
             didReturnDouble0 &&
             didReturnValueBetweenDouble0AndDoubleMaxValue &&
             didReturnMaxDoubleValue)
         {
            break;
         }
      }
      //
      IS_TRUE(didReturnLowestDoubleValue);
      IS_TRUE(didReturnValueBetweenDoubleMinValueAnd0);
      IS_TRUE(didReturnDouble0);
      IS_TRUE(didReturnValueBetweenDouble0AndDoubleMaxValue);
      IS_TRUE(didReturnMaxDoubleValue);
   }

   TEST(Random_ConstCharPointer_ReturnsRandomConstCharPointer1Through10)
   {
      set<const char*> randomConstCharPointers;
      //
      for (size_t i = 0; i < 300; ++i)
      {
         const char* const randonConstCharPointer = Random<const char*>();
         randomConstCharPointers.insert(randonConstCharPointer);
      }
      //
      for (const char* randomConstCharPointer : randomConstCharPointers)
      {
         REGEX_MATCHES("RandomConstCharPointer\\d+", randomConstCharPointer);
      }
   }

   TEST(Random_ConstWCharTPointer_CodeCoverage)
   {
      // 1000 iterations for code coverage of all ten branches
      for (size_t i = 0; i < 1000; ++i)
      {
         Random<const wchar_t*>();
      }
   }

   TEST(Random_FilesystemPath_ReturnsFilesystemPathWithBetween0And2Subfolders)
   {
      // 100 iterations for code coverage of the for-loop and hasFileExtension if-statement
      for (size_t i = 0; i < 100; ++i)
      {
         Random<std::filesystem::path>();
      }
   }

   TEST(Random_ErrorCode_ReturnsEitherGenericCategoryOrIostreamCategoryOrSystemCategoryErrorCode)
   {
      // 100 iterations for code coverage of all three branches
      for (size_t i = 0; i < 100; ++i)
      {
         Random<error_code>();
      }
   }

   TEST(Random_String_ReturnsRandomString1Through10)
   {
      set<string> randomStrings;
      //
      // 1000 iterations for code coverage of all ten branches
      for (size_t i = 0; i < 1000; ++i)
      {
         string randomString = Random<string>();
         randomStrings.emplace(randomString);
      }
      //
      for (const string& randomString : randomStrings)
      {
         REGEX_MATCHES("RandomString\\d+", randomString);
      }
   }

   TEST(Random_WideString_CodeCoverage)
   {
      // 1000 iterations for code coverage of all ten branches
      for (size_t i = 0; i < 1000; ++i)
      {
         Random<wstring>();
      }
   }

   TEST(RandomLetter_ReturnsUppercaseAThroughZ50PercentOfTheTime_ReturnsLowercaseAThroughZ50PercentOfTheTime)
   {
      bool uppercaseLetterReturned = false;
      bool lowercaseLetterReturned = false;
      for (size_t i = 0; i < 100; ++i)
      {
         const char randomLetter = ZenUnit::RandomLetter();
         if (isupper(randomLetter))
         {
            uppercaseLetterReturned = true;
         }
         if (islower(randomLetter))
         {
            lowercaseLetterReturned = true;
         }
         if (uppercaseLetterReturned && lowercaseLetterReturned)
         {
            break;
         }
      }
      IS_TRUE(uppercaseLetterReturned);
      IS_TRUE(lowercaseLetterReturned);
   }

   TEST(RandomWideLetter_ReturnsUppercaseAThroughZ50PercentOfTheTime_ReturnsLowercaseAThroughZ50PercentOfTheTime)
   {
      bool uppercaseLetterReturned = false;
      bool lowercaseLetterReturned = false;
      for (size_t i = 0; i < 100; ++i)
      {
         const wchar_t randomWideLetter = ZenUnit::RandomWideLetter();
         if (isupper(randomWideLetter))
         {
            uppercaseLetterReturned = true;
         }
         if (islower(randomWideLetter))
         {
            lowercaseLetterReturned = true;
         }
         if (uppercaseLetterReturned && lowercaseLetterReturned)
         {
            break;
         }
      }
      IS_TRUE(uppercaseLetterReturned);
      IS_TRUE(lowercaseLetterReturned);
   }

   TEST(RandomStringWithLength_ReturnsRandomStringWithLength)
   {
      const size_t length = ZenUnit::RandomBetween<size_t>(0, 3);
      //
      const string randomStringWithLength = ZenUnit::RandomStringWithLength(length);
      //
      ARE_EQUAL(length, randomStringWithLength.size());
      for (size_t i = 0; i < length; ++i)
      {
         const char ithCharacter = randomStringWithLength[i];
         IS_GREATER_THAN_OR_EQUAL(ithCharacter, 'A');
         IS_LESS_THAN_OR_EQUAL(ithCharacter, 'z');
      }
   }

   TEST(RandomWideStringWithLength_ReturnsRandomWideStringWithLength)
   {
      const size_t length = ZenUnit::RandomBetween<size_t>(1, 3);
      //
      const wstring randomWideStringWithLength = ZenUnit::RandomWideStringWithLength(length);
      //
      ARE_EQUAL(length, randomWideStringWithLength.size());
      for (size_t i = 0; i < length; ++i)
      {
         const wchar_t ithWideCharacter = randomWideStringWithLength[i];
         IS_GREATER_THAN_OR_EQUAL(ithWideCharacter, L'A');
         IS_LESS_THAN_OR_EQUAL(ithWideCharacter, L'z');
      }
   }

   TEST(RandomBetween_ReturnsRandomValueBetweenInclusiveLowerBoundAndInclusiveUpperBound)
   {
      bool randomBetweenReturnedNegative3 = false;
      bool randomBetweenReturnedNegative2 = false;
      bool randomBetweenReturnedNegative1 = false;
      bool randomBetweenReturned0 = false;
      bool randomBetweenReturnedPositive1 = false;
      bool randomBetweenReturnedPositive2 = false;
      bool randomBetweenReturnedPositive3 = false;
      for (size_t i = 0; i < 100000; ++i)
      {
         const long long randomLongLong = RandomBetween<long long>(-3, 3);
         if (randomLongLong == -3)
         {
            randomBetweenReturnedNegative3 = true;
         }
         else if (randomLongLong == -2)
         {
            randomBetweenReturnedNegative2 = true;
         }
         else if (randomLongLong == -1)
         {
            randomBetweenReturnedNegative1 = true;
         }
         else if (randomLongLong == 0)
         {
            randomBetweenReturned0 = true;
         }
         else if (randomLongLong == 1)
         {
            randomBetweenReturnedPositive1 = true;
         }
         else if (randomLongLong == 2)
         {
            randomBetweenReturnedPositive2 = true;
         }
         else if (randomLongLong == 3)
         {
            randomBetweenReturnedPositive3 = true;
         }
         if (randomBetweenReturnedNegative3 &&
             randomBetweenReturnedNegative2 &&
             randomBetweenReturnedNegative1 &&
             randomBetweenReturned0 &&
             randomBetweenReturnedPositive1 &&
             randomBetweenReturnedPositive2 &&
             randomBetweenReturnedPositive3)
         {
            break;
         }
      }
      IS_TRUE(randomBetweenReturnedNegative3);
      IS_TRUE(randomBetweenReturnedNegative2);
      IS_TRUE(randomBetweenReturnedNegative1);
      IS_TRUE(randomBetweenReturned0);
      IS_TRUE(randomBetweenReturnedPositive1);
      IS_TRUE(randomBetweenReturnedPositive2);
      IS_TRUE(randomBetweenReturnedPositive3);
   }

   TEST(RandomFloatBetween_ReturnsRandomFloatBetweenInclusiveLowerBoundAndInclusiveUpperBound)
   {
      for (size_t i = 0; i < 10000; ++i)
      {
         const float randomFloatBetween = ZenUnit::RandomFloatBetween(-3.0f, 3.0f);
         if (randomFloatBetween < -3.0f || randomFloatBetween > 3.0f)
         {
            FAIL_TEST("ZenUnit::RandomFloatBetween(-3.0f, 3.0f) unexpectedly returned out-of-bounds value"); // LCOV_EXCL_LINE
         }
      }
   }

   TEST(RandomDoubleBetween_ReturnsRandomDoubleBetweenInclusiveLowerBoundAndInclusiveUpperBound)
   {
      for (size_t i = 0; i < 10000; ++i)
      {
         const double randomDoubleBetween = ZenUnit::RandomDoubleBetween(-3.0, 3.0);
         if (randomDoubleBetween < -3.0 || randomDoubleBetween > 3.0)
         {
            FAIL_TEST("ZenUnit::RandomDoubleBetween(-3.0, 3.0) unexpectedly returned out-of-bounds value"); // LCOV_EXCL_LINE
         }
      }
   }

   TEST(RandomSizeTBetween_InclusiveLowerBoundEqualsInclusiveUpperBound_ReturnsInclusiveLowerBound)
   {
      const size_t randomSizeT00 = RandomSizeTBetween(0, 0);
      ARE_EQUAL(0, randomSizeT00);

      const size_t randomSizeT1010 = RandomSizeTBetween(10, 10);
      ARE_EQUAL(10, randomSizeT1010);
   }

   TEST(RandomSizeTBetween_ReturnsRandomValueBetweenInclusiveLowerBoundAndInclusiveUpperBound)
   {
      bool randomBetweenReturned3 = false;
      bool randomBetweenReturned4 = false;
      bool randomBetweenReturned5 = false;
      bool randomBetweenReturned6 = false;
      bool randomBetweenReturned7 = false;
      bool randomBetweenReturned8 = false;
      bool randomBetweenReturned9 = false;
      for (size_t i = 0; i < 10000; ++i)
      {
         const size_t randomSizeT = RandomSizeTBetween(3, 9);
         if (randomSizeT == 3)
         {
            randomBetweenReturned3 = true;
         }
         else if (randomSizeT == 4)
         {
            randomBetweenReturned4 = true;
         }
         else if (randomSizeT == 5)
         {
            randomBetweenReturned5 = true;
         }
         else if (randomSizeT == 6)
         {
            randomBetweenReturned6 = true;
         }
         else if (randomSizeT == 7)
         {
            randomBetweenReturned7 = true;
         }
         else if (randomSizeT == 8)
         {
            randomBetweenReturned8 = true;
         }
         else if (randomSizeT == 9)
         {
            randomBetweenReturned9 = true;
         }
         if (randomBetweenReturned3 &&
             randomBetweenReturned4 &&
             randomBetweenReturned5 &&
             randomBetweenReturned6 &&
             randomBetweenReturned7 &&
             randomBetweenReturned8 &&
             randomBetweenReturned9)
         {
            break;
         }
      }
      IS_TRUE(randomBetweenReturned3);
      IS_TRUE(randomBetweenReturned4);
      IS_TRUE(randomBetweenReturned5);
      IS_TRUE(randomBetweenReturned6);
      IS_TRUE(randomBetweenReturned7);
      IS_TRUE(randomBetweenReturned8);
      IS_TRUE(randomBetweenReturned9);
   }

   TEST(RandomUnsignedLongLong_ReturnsRandomUnsignedLongLongBetween0AndUnsignedLongLongMaxValue)
   {
      unordered_set<unsigned long long> uniqueRandomValues;
      //
      for (size_t i = 0; i < 100; ++i)
      {
         const unsigned long long randomUnsignedLongLong = ZenUnit::RandomUnsignedLongLong();
         uniqueRandomValues.insert(randomUnsignedLongLong);
      }
      //
      IS_TRUE(uniqueRandomValues.size() >= 2);
   }

   TEST1X1(RandomUnsignedLongLongBetween0AndValue_ReturnsRandomUnsignedLongLongBetween0AndInclusiveMaxValue,
      size_t inclusiveMaxValue,
      0ULL,
      1ULL,
      2ULL,
      3ULL)
   {
      unordered_set<unsigned long long> uniqueRandomValues;
      //
      for (size_t i = 0; i < 1000; ++i)
      {
         const unsigned long long randomUnsignedLongLong = ZenUnit::RandomUnsignedLongLongBetween0AndValue(inclusiveMaxValue);
         uniqueRandomValues.insert(randomUnsignedLongLong);
      }
      //
      unordered_set<unsigned long long> expectedUniqueRandomValues;
      for (size_t x = 0; x <= inclusiveMaxValue; ++x)
      {
         expectedUniqueRandomValues.insert(x);
      }
      SETS_ARE_EQUAL(expectedUniqueRandomValues, uniqueRandomValues);
   }

   RUN_TESTS(RandomTests)


   template<typename T>
   TEMPLATE_TESTS(RandomLessThanTests, T)
   AFACT(RandomLessThan_ReturnsARandomValueBetweenTMinValueAndExclusiveUpperBoundMinus1)
   EVIDENCE

   TEST(RandomLessThan_ReturnsARandomValueBetweenTMinValueAndExclusiveUpperBoundMinus1)
   {
      for (size_t i = 0; i < 100; ++i)
      {
         const T randomTValue = ZenUnit::RandomLessThan<T>(3);
         IS_LESS_THAN(randomTValue, T{3});
      }
   }

   RUN_TEMPLATE_TESTS(RandomLessThanTests, short)
   THEN_RUN_TEMPLATE_TESTS(RandomLessThanTests, int)
   THEN_RUN_TEMPLATE_TESTS(RandomLessThanTests, long long)
   THEN_RUN_TEMPLATE_TESTS(RandomLessThanTests, unsigned long long)


   template<typename T>
   TEMPLATE_TESTS(RandomLessThanOrEqualToTests, T)
   AFACT(RandomLessThanOrEqualTo_ReturnsARandomValueBetweenTMinValueAndInclusiveUpperBound)
   EVIDENCE

   TEST(RandomLessThanOrEqualTo_ReturnsARandomValueBetweenTMinValueAndInclusiveUpperBound)
   {
      for (size_t i = 0; i < 100; ++i)
      {
         const T randomTValue = ZenUnit::RandomLessThanOrEqualTo<T>(3);
         IS_LESS_THAN_OR_EQUAL(randomTValue, T{3});
      }
   }

   RUN_TEMPLATE_TESTS(RandomLessThanOrEqualToTests, short)
   THEN_RUN_TEMPLATE_TESTS(RandomLessThanOrEqualToTests, int)
   THEN_RUN_TEMPLATE_TESTS(RandomLessThanOrEqualToTests, long long)
   THEN_RUN_TEMPLATE_TESTS(RandomLessThanOrEqualToTests, unsigned long long)


   template<typename T>
   TEMPLATE_TESTS(RandomGreaterThanOrEqualToTests, T)
   AFACT(RandomGreaterThanOrEqualTo_ReturnsARandomValueBetweenInclusiveLowerBoundAndTMaxValue)
   EVIDENCE

   TEST(RandomGreaterThanOrEqualTo_ReturnsARandomValueBetweenInclusiveLowerBoundAndTMaxValue)
   {
      for (size_t i = 0; i < 100; ++i)
      {
         const T randomTValue = ZenUnit::RandomGreaterThanOrEqualTo<T>(3);
         IS_GREATER_THAN_OR_EQUAL(randomTValue, T{3});
      }
   }

   RUN_TEMPLATE_TESTS(RandomGreaterThanOrEqualToTests, short)
   THEN_RUN_TEMPLATE_TESTS(RandomGreaterThanOrEqualToTests, int)
   THEN_RUN_TEMPLATE_TESTS(RandomGreaterThanOrEqualToTests, long long)
   THEN_RUN_TEMPLATE_TESTS(RandomGreaterThanOrEqualToTests, unsigned long long)


   template<typename T>
   TEMPLATE_TESTS(RandomGreaterThanTests, T)
   AFACT(RandomGreaterThan_ReturnsARandomValueBetweenExclusiveLowerBoundPlus1AndTMaxValue)
   EVIDENCE

   TEST(RandomGreaterThan_ReturnsARandomValueBetweenExclusiveLowerBoundPlus1AndTMaxValue)
   {
      for (size_t i = 0; i < 100; ++i)
      {
         const T randomTValue = ZenUnit::RandomGreaterThan<T>(3);
         IS_GREATER_THAN(randomTValue, T{3});
      }
   }

   RUN_TEMPLATE_TESTS(RandomGreaterThanTests, short)
   THEN_RUN_TEMPLATE_TESTS(RandomGreaterThanTests, int)
   THEN_RUN_TEMPLATE_TESTS(RandomGreaterThanTests, long long)
   THEN_RUN_TEMPLATE_TESTS(RandomGreaterThanTests, unsigned long long)
}
