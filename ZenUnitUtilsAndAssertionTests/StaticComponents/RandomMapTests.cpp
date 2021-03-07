#include "pch.h"

namespace ZenUnit
{
   template<typename KeyType, typename ValueType>
   TEMPLATE_TESTS(RandomMapTests, KeyType, ValueType)
   FACTS(RandomOrderedMapWithSize_ReturnsAMapWithSpecifiedSize)
   AFACT(RandomOrderedMap_ReturnsAMapWithSizeBetween0And3)
   AFACT(RandomNonEmptyMap_ReturnsAMapWithSizeBetween1And3)
   FACTS(RandomUnorderedMapWithSize_ReturnsAnUnorderedMapWithSpecifiedSize)
   AFACT(RandomUnorderedMap_ReturnsAnUnorderedMapWithSizeBetween0And3)
   AFACT(RandomNonEmptyUnorderedMap_ReturnsAnUnorderedMapWithSizeBetween1And3)
   EVIDENCE

   TEST1X1(RandomOrderedMapWithSize_ReturnsAMapWithSpecifiedSize,
      size_t size,
      0ULL,
      1ULL,
      5ULL)
   {
      const map<KeyType, ValueType> randomOrderedMap = ZenUnit::RandomOrderedMapWithSize<KeyType, ValueType>(size);
      ARE_EQUAL(size, randomOrderedMap.size());
   }

   TEST(RandomOrderedMap_ReturnsAMapWithSizeBetween0And3)
   {
      const map<KeyType, ValueType> randomOrderedMap = ZenUnit::RandomOrderedMap<KeyType, ValueType>();
      IS_TRUE(randomOrderedMap.size() >= 0 && randomOrderedMap.size() <= 3);
   }

   TEST(RandomNonEmptyMap_ReturnsAMapWithSizeBetween1And3)
   {
      const map<KeyType, ValueType> randomNonEmptyOrderedMap = ZenUnit::RandomNonEmptyMap<KeyType, ValueType>();
      IS_TRUE(randomNonEmptyOrderedMap.size() >= 1 && randomNonEmptyOrderedMap.size() <= 3);
   }

   TEST1X1(RandomUnorderedMapWithSize_ReturnsAnUnorderedMapWithSpecifiedSize,
      size_t size,
      0ULL,
      1ULL,
      5ULL)
   {
      const unordered_map<KeyType, ValueType> randomOrderedMap = ZenUnit::RandomUnorderedMapWithSize<KeyType, ValueType>(size);
      ARE_EQUAL(size, randomOrderedMap.size());
   }

   TEST(RandomUnorderedMap_ReturnsAnUnorderedMapWithSizeBetween0And3)
   {
      const unordered_map<KeyType, ValueType> randomUnorderedMap = ZenUnit::RandomUnorderedMap<KeyType, ValueType>();
      IS_TRUE(randomUnorderedMap.size() >= 0 && randomUnorderedMap.size() <= 3);
   }

   TEST(RandomNonEmptyUnorderedMap_ReturnsAnUnorderedMapWithSizeBetween1And3)
   {
      const unordered_map<KeyType, ValueType> randomNonEmptyUnorderedMap = ZenUnit::RandomNonEmptyUnorderedMap<KeyType, ValueType>();
      IS_TRUE(randomNonEmptyUnorderedMap.size() >= 1 && randomNonEmptyUnorderedMap.size() <= 3);
   }

   RUN_TEMPLATE_TESTS(RandomMapTests, int, int)
   THEN_RUN_TEMPLATE_TESTS(RandomMapTests, string, double)
}
