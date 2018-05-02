#include "pch.h"

namespace ZenUnit
{
   TESTS(RandomTests)
   AFACT(Random_AllIntegerTypes_ReturnsRandomValueBetweenMinAndMaxForThatType)
   AFACT(Random_Float_ReturnsRandomFloat)
   AFACT(Random_Double_ReturnsRandomDouble)
   AFACT(Random_String_ReturnsRandomStringThatBeginsWithRandomString)
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

   TEST(Random_Float_ReturnsRandomFloat)
   {
      Random<float>();
   }

   TEST(Random_Double_ReturnsRandomDouble)
   {
      Random<double>();
   }

   TEST(Random_String_ReturnsRandomStringThatBeginsWithRandomString)
   {
      const string randomString = Random<string>();
      IS_TRUE(randomString.find("RandomString") != string::npos);
   }

   TEST(RandomBetween_ReturnsRandomValueBetweenInclusiveLowerBoundAndInclusiveUpperBound)
   {
      const int randomInt = RandomBetween<int>(1, 3);
      IS_TRUE(randomInt >= 1 && randomInt <= 3, "randomInt = " + to_string(randomInt));

      enum Enum
      {
         A,
         B,
         C
      };
      const Enum randomEnum = RandomBetween<Enum>(Enum::A, Enum::C);
      IS_TRUE(randomEnum >= Enum::A && randomEnum <= Enum::C, "randomEnum = " + to_string(randomEnum));
   }

   RUN_TESTS(RandomTests)


   template<typename T>
   TEMPLATE_TESTS(RandomVectorTests, T)
   AFACT(RandomVector_ReturnsAVectorWithSizeBetween0And2WithRandomElements)
   EVIDENCE

   TEST(RandomVector_ReturnsAVectorWithSizeBetween0And2WithRandomElements)
   {
      const vector<T> randomVector = ZenUnit::RandomVector<T>();
      IS_TRUE(randomVector.size() >= 0 && randomVector.size() <= 2);
   }

   RUN_TEMPLATE_TESTS(RandomVectorTests, int)
   THEN_RUN_TEMPLATE_TESTS(RandomVectorTests, string)


   template<typename KeyType, typename ValueType>
   TEMPLATE_TESTS(RandomMapTests, KeyType, ValueType)
   AFACT(RandomMap_ReturnsAMapWithSizeBetween0And2WithRandomElements)
   EVIDENCE

   TEST(RandomMap_ReturnsAMapWithSizeBetween0And2WithRandomElements)
   {
      const map<KeyType, ValueType> randomOrderedMap = ZenUnit::RandomMap<KeyType, ValueType>();
      IS_TRUE(randomOrderedMap.size() >= 0 && randomOrderedMap.size() <= 2);
   }
   RUN_TEMPLATE_TESTS(RandomMapTests, int, int)
   THEN_RUN_TEMPLATE_TESTS(RandomMapTests, string, double)


   template<typename KeyType, typename ValueType>
   TEMPLATE_TESTS(RandomUnorderedMapTests, KeyType, ValueType)
   AFACT(RandomUnorderedMap_ReturnsAMapWithSizeBetween0And2WithRandomElements)
   EVIDENCE

   TEST(RandomUnorderedMap_ReturnsAMapWithSizeBetween0And2WithRandomElements)
   {
      const unordered_map<KeyType, ValueType> randomUnorderedMap = ZenUnit::RandomUnorderedMap<KeyType, ValueType>();
      IS_TRUE(randomUnorderedMap.size() >= 0 && randomUnorderedMap.size() <= 2);
   }
   RUN_TEMPLATE_TESTS(RandomUnorderedMapTests, int, int)
   THEN_RUN_TEMPLATE_TESTS(RandomUnorderedMapTests, string, double)
}
