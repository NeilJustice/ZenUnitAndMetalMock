#include "pch.h"
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
   AFACT(Random_ConstWCharTPointer_ReturnsRandomConstWCharTPointer1Through10)
   AFACT(Random_FilesystemPath_ReturnsFilesystemPathWithBetween0And2Subfolders)
   AFACT(Random_ErrorCode_ReturnsEitherGenericCategoryOrIostreamCategoryOrSystemCategoryErrorCode)
   AFACT(Random_String_ReturnsRandomString1Through10)
   AFACT(Random_WideString_ReturnsRandomWideString1Through10)
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
      for (size_t i = 0; i < 100; ++i)
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
      for (size_t i = 0; i < 100; ++i)
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
      const set<const char*> expectedRandomConstCharPointers =
      {
         "RandomConstCharPointer1",
         "RandomConstCharPointer2",
         "RandomConstCharPointer3",
         "RandomConstCharPointer4",
         "RandomConstCharPointer5",
         "RandomConstCharPointer6",
         "RandomConstCharPointer7",
         "RandomConstCharPointer8",
         "RandomConstCharPointer9",
         "RandomConstCharPointer10"
      };
      SETS_ARE_EQUAL(expectedRandomConstCharPointers, randomConstCharPointers);
   }

   TEST(Random_ConstWCharTPointer_ReturnsRandomConstWCharTPointer1Through10)
   {
      set<const wchar_t*> randomWideConstCharPointers;
      //
      for (size_t i = 0; i < 300; ++i)
      {
         const wchar_t* const randomWideConstCharPointer = Random<const wchar_t*>();
         randomWideConstCharPointers.insert(randomWideConstCharPointer);
      }
      //
      const set<const wchar_t*> expectedRandomWideConstCharPointers =
      {
         L"RandomWideConstCharPointer1",
         L"RandomWideConstCharPointer2",
         L"RandomWideConstCharPointer3",
         L"RandomWideConstCharPointer4",
         L"RandomWideConstCharPointer5",
         L"RandomWideConstCharPointer6",
         L"RandomWideConstCharPointer7",
         L"RandomWideConstCharPointer8",
         L"RandomWideConstCharPointer9",
         L"RandomWideConstCharPointer10"
      };
      SETS_ARE_EQUAL(expectedRandomWideConstCharPointers, randomWideConstCharPointers);
   }

   TEST(Random_FilesystemPath_ReturnsFilesystemPathWithBetween0And2Subfolders)
   {
      // 30 iterations for code coverage of the for-loop and hasFileExtension if-statement
      for (size_t i = 0; i < 30; ++i)
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
      for (size_t i = 0; i < 300; ++i)
      {
         const string randomString = Random<string>();
         randomStrings.insert(randomString);
      }
      //
      const set<string> expectedRandomStrings =
      {
         "RandomString1",
         "RandomString2",
         "RandomString3",
         "RandomString4",
         "RandomString5",
         "RandomString6",
         "RandomString7",
         "RandomString8",
         "RandomString9",
         "RandomString10"
      };
      SETS_ARE_EQUAL(expectedRandomStrings, randomStrings);
   }

   TEST(Random_WideString_ReturnsRandomWideString1Through10)
   {
      set<wstring> randomStrings;
      //
      for (size_t i = 0; i < 300; ++i)
      {
         const wstring randomString = Random<wstring>();
         randomStrings.insert(randomString);
      }
      //
      const set<wstring> expectedRandomStrings =
      {
         L"RandomWString1",
         L"RandomWString2",
         L"RandomWString3",
         L"RandomWString4",
         L"RandomWString5",
         L"RandomWString6",
         L"RandomWString7",
         L"RandomWString8",
         L"RandomWString9",
         L"RandomWString10"
      };
      SETS_ARE_EQUAL(expectedRandomStrings, randomStrings);
   }

   TEST(RandomBetween_ReturnsRandomValueBetweenInclusiveLowerBoundAndInclusiveUpperBound)
   {
      bool randomBetweenReturnedNegative2 = false;
      bool randomBetweenReturnedNegative1 = false;
      bool randomBetweenReturned0 = false;
      bool randomBetweenReturnedPositive1 = false;
      bool randomBetweenReturnedPositive2 = false;
      for (size_t i = 0; i < 300; ++i)
      {
         const long long randomLongLong = RandomBetween<long long>(-2, 2);
         if (randomLongLong == -2)
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
         if (randomBetweenReturnedNegative2 &&
             randomBetweenReturnedNegative1 &&
             randomBetweenReturned0 &&
             randomBetweenReturnedPositive1 &&
             randomBetweenReturnedPositive2)
         {
            break;
         }
      }
      IS_TRUE(randomBetweenReturnedNegative2);
      IS_TRUE(randomBetweenReturnedNegative1);
      IS_TRUE(randomBetweenReturned0);
      IS_TRUE(randomBetweenReturnedPositive1);
      IS_TRUE(randomBetweenReturnedPositive2);
   }

   TEST(RandomUnsignedLongLong_ReturnsRandomUnsignedLongLongBetween0AndUnsignedLongLongMaxValue)
   {
      unordered_set<unsigned long long> uniqueRandomValues;
      //
      for (size_t i = 0; i < 10; ++i)
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
      for (size_t i = 0; i < 100; ++i)
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
      set<T> randomValuesReturned;
      //
      const T minTValue = std::numeric_limits<T>::min();
      for (size_t i = 0; i < 100; ++i)
      {
         const T randomT = ZenUnit::RandomLessThan<T>(minTValue + 3);
         randomValuesReturned.emplace(randomT);
      }
      //
      const set<T> expectedRandomValuesReturned =
      {
         minTValue,
         minTValue + 1,
         minTValue + 2
      };
      SETS_ARE_EQUAL(expectedRandomValuesReturned, randomValuesReturned);
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
      set<T> randomValuesReturned;
      //
      const T minTValue = std::numeric_limits<T>::min();
      for (size_t i = 0; i < 100; ++i)
      {
         const T randomT = ZenUnit::RandomLessThanOrEqualTo<T>(minTValue + 3);
         randomValuesReturned.emplace(randomT);
      }
      //
      const set<T> expectedRandomValuesReturned =
      {
         minTValue,
         minTValue + 1,
         minTValue + 2,
         minTValue + 3
      };
      SETS_ARE_EQUAL(expectedRandomValuesReturned, randomValuesReturned);
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
      set<T> randomValuesReturned;
      //
      const T maxTValue = std::numeric_limits<T>::max();
      for (size_t i = 0; i < 100; ++i)
      {
         const T randomT = ZenUnit::RandomGreaterThanOrEqualTo<T>(maxTValue - 3);
         randomValuesReturned.emplace(randomT);
      }
      //
      const set<T> expectedRandomValuesReturned =
      {
         maxTValue - 3,
         maxTValue - 2,
         maxTValue - 1,
         maxTValue
      };
      SETS_ARE_EQUAL(expectedRandomValuesReturned, randomValuesReturned);
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
      set<T> randomValuesReturned;
      //
      const T maxTValue = std::numeric_limits<T>::max();
      for (size_t i = 0; i < 100; ++i)
      {
         const T randomT = ZenUnit::RandomGreaterThan<T>(maxTValue - 3);
         randomValuesReturned.emplace(randomT);
      }
      //
      const set<T> expectedRandomValuesReturned =
      {
         maxTValue - 2,
         maxTValue - 1,
         maxTValue
      };
      SETS_ARE_EQUAL(expectedRandomValuesReturned, randomValuesReturned);
   }

   RUN_TEMPLATE_TESTS(RandomGreaterThanTests, short)
   THEN_RUN_TEMPLATE_TESTS(RandomGreaterThanTests, int)
   THEN_RUN_TEMPLATE_TESTS(RandomGreaterThanTests, long long)
   THEN_RUN_TEMPLATE_TESTS(RandomGreaterThanTests, unsigned long long)
}
