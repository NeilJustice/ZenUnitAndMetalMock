#include "pch.h"

namespace ZenUnit
{
   TESTS(RandomTests)
   AFACT(Random_AllIntegerTypes_ReturnsRandomValueBetweenMinAndMaxForThatType)
   AFACT(RandomNon0_ReturnsRandomValueBetweenMinAndMaxForThatTypeButNeverZero)
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

   TEST(Random_String_ReturnsRandomStringThatBeginsWithRandomString)
   {
      const string randomString = Random<string>();
      IS_TRUE(randomString.find("RS") != string::npos);
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
      IS_TRUE(randomVector.size() >= 0 && randomVector.size() <= 3);
   }
   RUN_TEMPLATE_TESTS(RandomVectorTests, int)
   THEN_RUN_TEMPLATE_TESTS(RandomVectorTests, string)


   template<typename T>
   TEMPLATE_TESTS(RandomNonEmptyVectorTests, T)
   AFACT(RandomNonEmptyVector_ReturnsAVectorWithSizeBetween0And2WithRandomElements)
   EVIDENCE
   TEST(RandomNonEmptyVector_ReturnsAVectorWithSizeBetween0And2WithRandomElements)
   {
      const vector<T> randomNonEmptyVector = ZenUnit::RandomNonEmptyVector<T>();
      IS_TRUE(randomNonEmptyVector.size() >= 1 && randomNonEmptyVector.size() <= 3);
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