#include "pch.h"
#include "ZenUnitUtilsAndAssertionTests/Assertions/REGEX_MATCHES.h"
#include <numeric> // std::iota

namespace ZenUnit
{
   TESTS(RandomTests)
   AFACT(Random_Enum_ReturnsRandomEnumBetween0AndEnumMaxValue)
   AFACT(RandomNon0_Enum_ReturnsRandomEnumBetween1AndEnumMaxValue)
   AFACT(Random_AllIntegerTypes_ReturnsRandomValueBetweenMinAndMaxForThatType)
   AFACT(Random_TIsAPair_ReturnsRandomPair)
   AFACT(Random_TIsAVector_ReturnsRandomVectorOfTWithSizeLessThanOrEqualTo3)
   AFACT(Random_TIsAnUnorderedMap_ReturnsRandomUnorderedMap)
   AFACT(Random_TIsAnUnorderedSet_ReturnsRandomUnorderedSet)
   AFACT(RandomNon0_ReturnsNon0RandomValueBetweenMinAndMaxForTypeT)
   AFACT(RandomNotEqualToValue_ReturnsRandomValueBetweenMinAndMaxForTypeTExceptForTheExceptValue)
   AFACT(Random_Float_ReturnsRandomFloat)
   AFACT(Random_Double_ReturnsRandomDouble)
   AFACT(Random_ConstCharPointer_ReturnsRandomConstCharPointer1Through10)
   AFACT(Random_ConstWCharTPointer_CodeCoverage)
   AFACT(Random_FilesystemPath_ReturnsFilesystemPathWithBetween0And2Subfolders)
   AFACT(Random_ErrorCode_ReturnsEitherGenericCategoryOrIostreamCategoryOrSystemCategoryErrorCode)
   AFACT(Random_String_ReturnsRandomString1Through10)
   AFACT(Random_WideString_CodeCoverage)
   AFACT(RandomBetween_ReturnsRandomValueBetweenInclusiveLowerBoundAndInclusiveUpperBound)
   AFACT(RandomUnsignedLongLong_ReturnsRandomUnsignedLongLongBetween0AndUnsignedLongLongMaxValue)
   FACTS(RandomUnsignedLongLongBetween0AndValue_ReturnsRandomUnsignedLongLongBetween0AndInclusiveMaxValue)
   EVIDENCE

   TEST(Random_Enum_ReturnsRandomEnumBetween0AndEnumMaxValue)
   {
      enum class EnumType
      {
         ZeroValue,
         OneValue,
         TwoValue,
         MaxValue
      };
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

   TEST(RandomNon0_Enum_ReturnsRandomEnumBetween1AndEnumMaxValue)
   {
      enum class EnumType
      {
         ZeroValue,
         OneValue,
         TwoValue,
         MaxValue
      };
      set<EnumType> randomEnumsReturned;
      for (size_t i = 0; i < 1000; ++i)
      {
         const EnumType randomNon0Enum = RandomNon0<EnumType>();
         randomEnumsReturned.insert(randomNon0Enum);
      }
      const set<EnumType> expectedRandomEnumsReturned
      {
         EnumType::OneValue,
         EnumType::TwoValue
      };
      SETS_ARE_EQUAL(expectedRandomEnumsReturned, randomEnumsReturned);
   }

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

   TEST(RandomNotEqualToValue_ReturnsRandomValueBetweenMinAndMaxForTypeTExceptForTheExceptValue)
   {
      const char char1 = ZenUnit::Random<char>();
      const char char2 = ZenUnit::RandomNotEqualToValue<char>(char1);
      ARE_NOT_EQUAL(char1, char2);

      const unsigned char unsignedChar1 = ZenUnit::Random<unsigned char>();
      const unsigned char unsignedChar2 = ZenUnit::RandomNotEqualToValue<unsigned char>(unsignedChar1);
      ARE_NOT_EQUAL(unsignedChar1, unsignedChar2);

      const short short1 = ZenUnit::Random<short>();
      const short short2 = ZenUnit::RandomNotEqualToValue<short>(short1);
      ARE_NOT_EQUAL(short1, short2);

      const unsigned short unsignedShort1 = ZenUnit::Random<unsigned short>();
      const unsigned short unsignedShort2 = ZenUnit::RandomNotEqualToValue<unsigned short>(unsignedShort1);
      ARE_NOT_EQUAL(unsignedShort1, unsignedShort2);

      const int int1 = ZenUnit::Random<int>();
      const int int2 = ZenUnit::RandomNotEqualToValue<int>(int1);
      ARE_NOT_EQUAL(int1, int2);

      const unsigned int unsignedInt1 = ZenUnit::Random<unsigned int>();
      const unsigned int unsignedInt2 = ZenUnit::RandomNotEqualToValue<unsigned int>(unsignedInt1);
      ARE_NOT_EQUAL(unsignedInt1, unsignedInt2);

      const long long longLong1 = ZenUnit::Random<long long>();
      const long long longLong2 = ZenUnit::RandomNotEqualToValue<long long>(longLong1);
      ARE_NOT_EQUAL(longLong1, longLong2);

      const unsigned long long unsignedLongLong1 = ZenUnit::Random<unsigned long long>();
      const unsigned long long unsignedLongLong2 = ZenUnit::RandomNotEqualToValue<unsigned long long>(unsignedLongLong1);
      ARE_NOT_EQUAL(unsignedLongLong1, unsignedLongLong2);
   }

   TEST(Random_Float_ReturnsRandomFloat)
   {
      Random<float>();
   }

   TEST(Random_Double_ReturnsRandomDouble)
   {
      Random<double>();
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
         const unsigned long long randomUnsignedLongLongBetween0AndInclusiveMaxValue =
            ZenUnit::RandomUnsignedLongLongBetween0AndValue(inclusiveMaxValue);
         uniqueRandomValues.insert(randomUnsignedLongLongBetween0AndInclusiveMaxValue);
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
}

namespace ZenUnit
{
   template<typename T>
   TEMPLATE_TESTS(RandomLessThanTests, T)
   AFACT(RandomLessThan_ReturnsARandomValueBetweenTMinValueAndExclusiveUpperBoundMinus1)
   EVIDENCE

   TEST(RandomLessThan_ReturnsARandomValueBetweenTMinValueAndExclusiveUpperBoundMinus1)
   {
      const T randomTValue = ZenUnit::RandomLessThan<T>(3);
      IS_LT(randomTValue, T{3});
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
      const T randomTValue = ZenUnit::RandomLessThanOrEqualTo<T>(3);
      IS_LTE(randomTValue, T{3});
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
      const T randomTValue = ZenUnit::RandomGreaterThanOrEqualTo<T>(3);
      IS_GTE(randomTValue, T{3});
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
      const T randomTValue = ZenUnit::RandomGreaterThan<T>(3);
      IS_GT(randomTValue, T{3});
   }

   RUN_TEMPLATE_TESTS(RandomGreaterThanTests, short)
   THEN_RUN_TEMPLATE_TESTS(RandomGreaterThanTests, int)
   THEN_RUN_TEMPLATE_TESTS(RandomGreaterThanTests, long long)
   THEN_RUN_TEMPLATE_TESTS(RandomGreaterThanTests, unsigned long long)
}
