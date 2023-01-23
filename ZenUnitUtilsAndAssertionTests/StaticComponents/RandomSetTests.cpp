#include "pch.h"

namespace ZenUnit
{
   template<typename ElementType>
   TEMPLATE_TESTS(RandomSetTests, ElementType)
   FACTS(RandomOrderedSetWithSize_ReturnsAnOrderedSetWithSpecifiedSize)
   AFACT(RandomOrderedSet_ReturnsAnOrderedSetWithSizeBetween0And3)
   AFACT(RandomNonEmptyOrderedSet_ReturnsAnOrderedSetWithSizeBetween1And3)
   FACTS(RandomUnorderedSetWithSize_ReturnsAnOrderedSetWithSpecifiedSize)
   AFACT(RandomUnorderedSet_ReturnsAnUnorderedSetWithSizeBetween0And3)
   AFACT(RandomNonEmptyUnorderedSet_ReturnsAnUnorderedSetWithSizeBetween1And3)
   EVIDENCE

   TEST1X1(RandomOrderedSetWithSize_ReturnsAnOrderedSetWithSpecifiedSize,
      size_t size,
      1ULL,
      2ULL,
      5ULL)
   {
      const set<ElementType> randomOrderedSet = ZenUnit::RandomOrderedSetWithSize<ElementType>(size);
      ARE_EQUAL(size, randomOrderedSet.size());
   }

   TEST(RandomOrderedSet_ReturnsAnOrderedSetWithSizeBetween0And3)
   {
      const set<ElementType> randomOrderedSet = ZenUnit::RandomOrderedSet<ElementType>();
      IS_TRUE(randomOrderedSet.size() <= 3);
   }

   TEST(RandomNonEmptyOrderedSet_ReturnsAnOrderedSetWithSizeBetween1And3)
   {
      const set<ElementType> randomNonEmptyOrderedSet = ZenUnit::RandomNonEmptyOrderedSet<ElementType>();
      IS_TRUE(randomNonEmptyOrderedSet.size() >= 1 && randomNonEmptyOrderedSet.size() <= 3);
   }

   TEST1X1(RandomUnorderedSetWithSize_ReturnsAnOrderedSetWithSpecifiedSize,
      size_t size,
      1ULL,
      2ULL,
      5ULL)
   {
      const unordered_set<ElementType> randomUnorderedSet = ZenUnit::RandomUnorderedSetWithSize<ElementType>(size);
      ARE_EQUAL(size, randomUnorderedSet.size());
   }

   TEST(RandomUnorderedSet_ReturnsAnUnorderedSetWithSizeBetween0And3)
   {
      const unordered_set<ElementType> randomUnorderedSet = ZenUnit::RandomUnorderedSet<ElementType>();
      IS_TRUE(randomUnorderedSet.size() <= 3);
   }

   TEST(RandomNonEmptyUnorderedSet_ReturnsAnUnorderedSetWithSizeBetween1And3)
   {
      const unordered_set<ElementType> randomNonEmptyUnorderedSet = ZenUnit::RandomNonEmptyUnorderedSet<ElementType>();
      IS_TRUE(randomNonEmptyUnorderedSet.size() >= 1 && randomNonEmptyUnorderedSet.size() <= 3);
   }

   RUN_TEMPLATE_TESTS(RandomSetTests, int)
   THEN_RUN_TEMPLATE_TESTS(RandomSetTests, string)
}
