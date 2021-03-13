#include "pch.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATE_TESTS(RandomVectorTests, T)
   FACTS(RandomVectorWithSize_ReturnsAVectorWithSpecifiedSize)
   AFACT(RandomVector_ReturnsAVectorWithSizeBetween0And2)
   AFACT(RandomNonEmptyVector_ReturnsAVectorWithSizeBetween1And3)
   EVIDENCE

   TEST1X1(RandomVectorWithSize_ReturnsAVectorWithSpecifiedSize,
      size_t size,
      0ULL,
      1ULL,
      5ULL)
   {
      const vector<T> randomVectorWithSize = ZenUnit::RandomVectorWithSize<T>(size);
      ARE_EQUAL(size, randomVectorWithSize.size());
   }

   TEST(RandomVector_ReturnsAVectorWithSizeBetween0And2)
   {
      const vector<T> randomVector = ZenUnit::RandomVector<T>();
      IS_TRUE(randomVector.size() <= 3);
   }

   TEST(RandomNonEmptyVector_ReturnsAVectorWithSizeBetween1And3)
   {
      const vector<T> randomNonEmptyVector = ZenUnit::RandomNonEmptyVector<T>();
      IS_TRUE(randomNonEmptyVector.size() >= 1 && randomNonEmptyVector.size() <= 3);
   }

   RUN_TEMPLATE_TESTS(RandomVectorTests, int)
   THEN_RUN_TEMPLATE_TESTS(RandomVectorTests, string)
}
