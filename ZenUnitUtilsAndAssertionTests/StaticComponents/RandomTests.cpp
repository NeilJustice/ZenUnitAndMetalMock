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
   AFACT(Random0OrGreater_ReturnsRandomIntegerBetween0AndTMaxValue)
   AFACT(Random1OrGreater_ReturnsRandomIntegerBetween1AndTMaxValue)
   AFACT(RandomNegative_ReturnsRandomINtegerBetweenTMinValueAndNegative1)
   AFACT(Random_Float_ReturnsRandomFloat)
   AFACT(Random_Double_ReturnsRandomDouble)
   AFACT(Random_ConstCharPointer_ReturnsRandomConstCharPointer1Through10)
   AFACT(Random_ConstWCharTPointer_ReturnsRandomConstWCharTPointer1Through10)
   AFACT(Random_FilesystemPath_ReturnsFilesystemPathWithBetween0And2Subfolders)
   AFACT(Random_ErrorCode_ReturnsEitherGenericCategoryOrIostreamCategoryOrSystemCategoryErrorCode)
   AFACT(Random_String_ReturnsRandomString1Through10)
   AFACT(Random_WideString_ReturnsRandomWideString1Through10)
   AFACT(RandomBetween_ReturnsRandomValueBetweenInclusiveLowerBoundAndInclusiveUpperBound)
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
      set<unsigned char> randomNonZeroUnsignedChars;
      //
      for (size_t i = 0; i < 5000; ++i)
      {
         const unsigned char randomNonZeroUnsignedChar = RandomNon0<unsigned char>();
         randomNonZeroUnsignedChars.insert(randomNonZeroUnsignedChar);
      }
      //
      vector<unsigned char> expectedNonZeroUnsignedCharsAsVector(255);
      iota(expectedNonZeroUnsignedCharsAsVector.begin(), expectedNonZeroUnsignedCharsAsVector.end(), static_cast<unsigned char>(1));
      ARE_EQUAL(1, expectedNonZeroUnsignedCharsAsVector[0]);
      ARE_EQUAL(numeric_limits<unsigned char>::max(), expectedNonZeroUnsignedCharsAsVector.back());
      const set<unsigned char> expectedRandomNon0CharsAsUnorderedSet(
         expectedNonZeroUnsignedCharsAsVector.begin(), expectedNonZeroUnsignedCharsAsVector.end());
      SETS_ARE_EQUAL(expectedRandomNon0CharsAsUnorderedSet, randomNonZeroUnsignedChars);

      ARE_NOT_EQUAL(0, RandomNon0<char>());
      ARE_NOT_EQUAL(0, RandomNon0<short>());
      ARE_NOT_EQUAL(0, RandomNon0<unsigned short>());
      ARE_NOT_EQUAL(0, RandomNon0<int>());
      ARE_NOT_EQUAL(0, RandomNon0<unsigned int>());
      ARE_NOT_EQUAL(0, RandomNon0<long long>());
      ARE_NOT_EQUAL(0, RandomNon0<unsigned long long>());
   }

   TEST(RandomNotEqualToValue_ReturnsRandomValueBetweenMinAndMaxForTypeTExceptForTheExceptValue)
   {
      set<unsigned char> randomNonZeroUnsignedChars;
      //
      const unsigned char exceptValue = Random<unsigned char>();
      for (size_t i = 0; i < 5000; ++i)
      {
         const unsigned char randomNonZeroUnsignedChar = RandomNotEqualToValue<unsigned char>(exceptValue);
         randomNonZeroUnsignedChars.insert(randomNonZeroUnsignedChar);
      }
      //
      vector<unsigned char> expectedUnsignedCharsExceptForExceptValueAsVector(256);
      std::iota(expectedUnsignedCharsExceptForExceptValueAsVector.begin(),
         expectedUnsignedCharsExceptForExceptValueAsVector.end(),
         static_cast<unsigned char>(0));
      expectedUnsignedCharsExceptForExceptValueAsVector.erase(std::find(
         expectedUnsignedCharsExceptForExceptValueAsVector.begin(),
         expectedUnsignedCharsExceptForExceptValueAsVector.end(), exceptValue));
      const set<unsigned char> expectedUnsignedCharsExceptForExceptValueAsUnorderedSet(
         expectedUnsignedCharsExceptForExceptValueAsVector.begin(), expectedUnsignedCharsExceptForExceptValueAsVector.end());
      SETS_ARE_EQUAL(expectedUnsignedCharsExceptForExceptValueAsUnorderedSet, randomNonZeroUnsignedChars);


      const char notEqualCharValue = ZenUnit::Random<char>();
      ARE_NOT_EQUAL(notEqualCharValue, RandomNon0<char>());

      const short notEqualShortValue = ZenUnit::Random<short>();
      ARE_NOT_EQUAL(notEqualShortValue, RandomNon0<short>());

      const unsigned short notEqualUnsignedShortValue = ZenUnit::Random<unsigned short>();
      ARE_NOT_EQUAL(notEqualUnsignedShortValue, RandomNon0<unsigned short>());

      const int notEqualIntValue = ZenUnit::Random<int>();
      ARE_NOT_EQUAL(notEqualIntValue, RandomNon0<int>());

      const unsigned int notEqualUnsignedIntValue = ZenUnit::Random<unsigned int>();
      ARE_NOT_EQUAL(notEqualUnsignedIntValue, RandomNon0<unsigned int>());

      const long long notEqualLongLongValue = ZenUnit::Random<long long>();
      ARE_NOT_EQUAL(notEqualLongLongValue, RandomNon0<long long>());

      const unsigned long long notEqualUnsignedLongLongValue = ZenUnit::Random<unsigned long long>();
      ARE_NOT_EQUAL(notEqualUnsignedLongLongValue, RandomNon0<unsigned long long>());
   }

   TEST(Random0OrGreater_ReturnsRandomIntegerBetween0AndTMaxValue)
   {
      const int randomIntBetween0AndMaxValue = Random0OrGreater<int>();
      IS_TRUE(randomIntBetween0AndMaxValue >= 0);

      const long long randomLongLongBetween0AndMaxValue = Random0OrGreater<long long>();
      IS_TRUE(randomLongLongBetween0AndMaxValue >= 0);
   }

   TEST(Random1OrGreater_ReturnsRandomIntegerBetween1AndTMaxValue)
   {
      const int randomIntBetween1AndMaxValue = Random1OrGreater<int>();
      IS_TRUE(randomIntBetween1AndMaxValue >= 1);

      const long long randomLongLongBetween1AndMaxValue = Random1OrGreater<long long>();
      IS_TRUE(randomLongLongBetween1AndMaxValue >= 0);
   }

   TEST(RandomNegative_ReturnsRandomINtegerBetweenTMinValueAndNegative1)
   {
      const int randomIntBetweenMinValueAndNegative1 = RandomNegative<int>();
      IS_TRUE(randomIntBetweenMinValueAndNegative1 <= -1);

      const long long randomLongLongBetweenMinValueAndNegative1 = RandomNegative<long long>();
      IS_TRUE(randomLongLongBetweenMinValueAndNegative1 <= -1);
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

   RUN_TESTS(RandomTests)
}

namespace ZenUnit
{
   template<typename T>
   TEMPLATE_TESTS(RandomLessThanOrEqualToTests, T)
   AFACT(RandomLessThanOrEqualTo_ReturnsARandomValueBetweenInclusiveLowerBoundAndTMaxValue)
   EVIDENCE

   TEST(RandomLessThanOrEqualTo_ReturnsARandomValueBetweenInclusiveLowerBoundAndTMaxValue)
   {
      set<T> randomValuesReturned;
      //
      const T minTValue = std::numeric_limits<T>::min();
      for (size_t i = 0; i < 100; ++i)
      {
         const T randomT = ZenUnit::RandomLessThanOrEqualTo<T>(minTValue + 2);
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
         const T randomT = ZenUnit::RandomGreaterThanOrEqualTo<T>(maxTValue - 2);
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

   RUN_TEMPLATE_TESTS(RandomGreaterThanOrEqualToTests, short)
   THEN_RUN_TEMPLATE_TESTS(RandomGreaterThanOrEqualToTests, int)
   THEN_RUN_TEMPLATE_TESTS(RandomGreaterThanOrEqualToTests, long long)
   THEN_RUN_TEMPLATE_TESTS(RandomGreaterThanOrEqualToTests, unsigned long long)
}
