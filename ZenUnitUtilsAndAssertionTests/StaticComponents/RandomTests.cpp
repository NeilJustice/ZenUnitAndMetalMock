#include "pch.h"

namespace ZenUnit
{
   TESTS(RandomTests)
   AFACT(Random_AllIntegerTypes_ReturnsRandomValueBetweenMinAndMaxForThatType)
   AFACT(Random_TIsAVector_ReturnsRandomVectorOfTWithSizeLessThanOrEqualTo3)
   AFACT(Random_TIsAPair_ReturnsRandomPair)
   AFACT(Random_TIsAnUnorderedMap_ReturnsRandomUnorderedMap)
   AFACT(RandomNon0_ReturnsRandomValueBetweenMinAndMaxForThatTypeButNeverZero)
   AFACT(Random_Float_ReturnsRandomFloat)
   AFACT(Random_Double_ReturnsRandomDouble)
   AFACT(Random_ConstCharPointer_ReturnsRandomConstCharPointer1Through10)
   AFACT(Random_ErrorCode_ReturnsEitherGenericCategoryOrIostreamCategoryOrSystemCategoryErrorCode)
   AFACT(Random_String_ReturnsRandomStringThatBeginsWithRS)
   AFACT(Random_WideString_ReturnsRandomWideStringThatBeginsWithRWS)
   AFACT(RandomBetween_ReturnsRandomValueBetweenInclusiveLowerBoundAndInclusiveUpperBound)
   EVIDENCE

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

   TEST(Random_TIsAVector_ReturnsRandomVectorOfTWithSizeLessThanOrEqualTo3)
   {
      const vector<int> randomIntVector = Random<vector<int>>();
      IS_TRUE(randomIntVector.size() <= 3);

      const vector<string> randomStringVector = Random<vector<string>>();
      IS_TRUE(randomStringVector.size() <= 3);
   }

   TEST(Random_TIsAPair_ReturnsRandomPair)
   {
      [[maybe_unused]]
      const pair<int, string> randomIntStringPair = Random<pair<int, string>>();

      [[maybe_unused]]
      const pair<double, char> randomDoubleCharPair = Random<pair<double, char>>();
   }

   TEST(Random_TIsAnUnorderedMap_ReturnsRandomUnorderedMap)
   {
      [[maybe_unused]]
      const unordered_map<int, int> intIntUnorderedMap = Random<unordered_map<int, int>>();

      [[maybe_unused]]
      const unordered_map<string, double> stringDoubleUnorderedMap = Random<unordered_map<string, double>>();
   }

   TEST(RandomNon0_ReturnsRandomValueBetweenMinAndMaxForThatTypeButNeverZero)
   {
      RandomNon0<char>();
      RandomNon0<unsigned char>();
      RandomNon0<short>();
      RandomNon0<unsigned short>();
      RandomNon0<int>();
      RandomNon0<unsigned int>();
      RandomNon0<long long>();
      RandomNon0<unsigned long long>();
      RandomNon0<size_t>();
      enum EnumType {};
      RandomNon0<EnumType>();
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
      Random<const char*>();
   }

   TEST(Random_ErrorCode_ReturnsEitherGenericCategoryOrIostreamCategoryOrSystemCategoryErrorCode)
   {
      // 100 iterations for code coverage of all three branches
      for (size_t i = 0; i < 100; ++i)
      {
         Random<error_code>();
      }
   }

   TEST(Random_String_ReturnsRandomStringThatBeginsWithRS)
   {
      const string randomString = Random<string>();
      IS_TRUE(randomString.find("RS") != string::npos);
   }

   TEST(Random_WideString_ReturnsRandomWideStringThatBeginsWithRWS)
   {
      const wstring randomWideString = Random<wstring>();
      IS_TRUE(randomWideString.find(L"RWS") != string::npos);
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


   template<typename KeyType, typename ValueType>
   TEMPLATE_TESTS(RandomPairTests, KeyType, ValueType)
   AFACT(RandomPair_ReturnsPairWithRandomKeyAndRandomValue)
   EVIDENCE

   TEST(RandomPair_ReturnsPairWithRandomKeyAndRandomValue)
   {
      const pair<KeyType, ValueType> randomPair = ZenUnit::RandomPair<KeyType, ValueType>();
      IS_NOT_DEFAULT_VALUE(randomPair.first);
      IS_NOT_DEFAULT_VALUE(randomPair.second);
   }

   RUN_TEMPLATE_TESTS(RandomPairTests, int, int)
   THEN_RUN_TEMPLATE_TESTS(RandomPairTests, string, long long)


   template<typename T>
   TEMPLATE_TESTS(RandomVectorTests, T)
   AFACT(RandomVector_ReturnsAVectorWithSizeBetween0And2)
   EVIDENCE

   TEST(RandomVector_ReturnsAVectorWithSizeBetween0And2)
   {
      const vector<T> randomVector = ZenUnit::RandomVector<T>();
      IS_TRUE(randomVector.size() >= 0 && randomVector.size() <= 3);
   }

   RUN_TEMPLATE_TESTS(RandomVectorTests, int)
   THEN_RUN_TEMPLATE_TESTS(RandomVectorTests, string)


   template<typename T>
   TEMPLATE_TESTS(RandomVectorWithSizeTests, T)
   FACTS(RandomVectorWithSize_ReturnsAVectorWithSpecifiedSize)
   EVIDENCE

   TEST1X1(RandomVectorWithSize_ReturnsAVectorWithSpecifiedSize,
      size_t size,
      0ull,
      1ull,
      2ull)
   {
      const vector<T> randomVectorWithSize = ZenUnit::RandomVectorWithSize<T>(size);
      ARE_EQUAL(size, randomVectorWithSize.size());
   }

   RUN_TEMPLATE_TESTS(RandomVectorWithSizeTests, int)
   THEN_RUN_TEMPLATE_TESTS(RandomVectorWithSizeTests, string)


   template<typename T>
   TEMPLATE_TESTS(RandomNonEmptyVectorTests, T)
   AFACT(RandomNonEmptyVector_ReturnsAVectorWithSizeBetween1And3)
   EVIDENCE

   TEST(RandomNonEmptyVector_ReturnsAVectorWithSizeBetween1And3)
   {
      const vector<T> randomNonEmptyVector = ZenUnit::RandomNonEmptyVector<T>();
      IS_TRUE(randomNonEmptyVector.size() == 1 ||
              randomNonEmptyVector.size() == 2 ||
              randomNonEmptyVector.size() == 3);
   }

   RUN_TEMPLATE_TESTS(RandomNonEmptyVectorTests, int)
   THEN_RUN_TEMPLATE_TESTS(RandomNonEmptyVectorTests, string)


   template<typename KeyType, typename ValueType>
   TEMPLATE_TESTS(RandomMapTests, KeyType, ValueType)
   AFACT(RandomMap_ReturnsAMapWithSizeBetween0And2WithRandomElements)
   EVIDENCE

   TEST(RandomMap_ReturnsAMapWithSizeBetween0And2WithRandomElements)
   {
      const map<KeyType, ValueType> randomOrderedMap = ZenUnit::RandomMap<KeyType, ValueType>();
      IS_TRUE(randomOrderedMap.size() >= 0 && randomOrderedMap.size() <= 3);
   }

   RUN_TEMPLATE_TESTS(RandomMapTests, int, int)
   THEN_RUN_TEMPLATE_TESTS(RandomMapTests, string, double)


   template<typename KeyType, typename ValueType>
   TEMPLATE_TESTS(RandomUnorderedMapTests, KeyType, ValueType)
   AFACT(RandomUnorderedMap_ReturnsAnUnorderedMapWithSizeBetween0And3)
   EVIDENCE

   TEST(RandomUnorderedMap_ReturnsAnUnorderedMapWithSizeBetween0And3)
   {
      const unordered_map<KeyType, ValueType> randomUnorderedMap = ZenUnit::RandomUnorderedMap<KeyType, ValueType>();
      IS_TRUE(randomUnorderedMap.size() >= 0 && randomUnorderedMap.size() <= 3);
   }

   RUN_TEMPLATE_TESTS(RandomUnorderedMapTests, int, int)
   THEN_RUN_TEMPLATE_TESTS(RandomUnorderedMapTests, string, double)


   template<typename ElementType>
   TEMPLATE_TESTS(RandomSetTests, ElementType)
   AFACT(RandomSet_ReturnsAnUnorderedSetWithSizeBetween0And3)
   EVIDENCE
   TEST(RandomSet_ReturnsAnUnorderedSetWithSizeBetween0And3)
   {
      const set<ElementType> randomSet = ZenUnit::RandomSet<ElementType>();
      IS_TRUE(randomSet.size() >= 0 && randomSet.size() <= 3);
   }
   RUN_TEMPLATE_TESTS(RandomSetTests, int)
   THEN_RUN_TEMPLATE_TESTS(RandomSetTests, string)


   template<typename ElementType>
   TEMPLATE_TESTS(RandomUnorderedSetTests, ElementType)
   AFACT(RandomUnorderedSet_ReturnsAnUnorderedSetWithSizeBetween0And3)
   EVIDENCE

   TEST(RandomUnorderedSet_ReturnsAnUnorderedSetWithSizeBetween0And3)
   {
      const unordered_set<ElementType> randomUnorderedSet = ZenUnit::RandomUnorderedSet<ElementType>();
      IS_TRUE(randomUnorderedSet.size() >= 0 && randomUnorderedSet.size() <= 3);
   }

   RUN_TEMPLATE_TESTS(RandomUnorderedSetTests, int)
   THEN_RUN_TEMPLATE_TESTS(RandomUnorderedSetTests, string)
}
