#include "pch.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATE_TESTS(RandomSpanTests, T)
   FACTS(RandomSpanWithSize_ReturnsASpanWithSpecifiedSize)
   AFACT(RandomSpan_ReturnsASpanWithSizeBetween0And2)
   AFACT(RandomNonEmptySpan_ReturnsASpanWithSizeBetween1And3)
   EVIDENCE

   TEST1X1(RandomSpanWithSize_ReturnsASpanWithSpecifiedSize,
      size_t size,
      0ULL,
      1ULL,
      5ULL)
   {
      const span<const T> randomSpanWithSize = ZenUnit::RandomSpanWithSize<T>(size);
      ARE_EQUAL(size, randomSpanWithSize.size());
   }

   TEST(RandomSpan_ReturnsASpanWithSizeBetween0And2)
   {
      const span<const T> randomSpan = ZenUnit::RandomSpan<T>();
      IS_TRUE(randomSpan.size() <= 3);
   }

   TEST(RandomNonEmptySpan_ReturnsASpanWithSizeBetween1And3)
   {
      const span<const T> randomNonEmptySpan = ZenUnit::RandomNonEmptySpan<T>();
      IS_TRUE(randomNonEmptySpan.size() >= 1 && randomNonEmptySpan.size() <= 3);
   }

   RUN_TEMPLATE_TESTS(RandomSpanTests, int)
   THEN_RUN_TEMPLATE_TESTS(RandomSpanTests, string)
}
