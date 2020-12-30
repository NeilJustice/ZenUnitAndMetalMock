#include "pch.h"

namespace ZenUnit
{
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


   template<typename T, size_t Size>
   TEMPLATE_TESTS(RandomStdArrayTests, T, Size)
   AFACT(RandomStdArray_ReturnsStdArrayWithAllRandomValues)
   EVIDENCE

   TEST(RandomStdArray_ReturnsStdArrayWithAllRandomValues)
   {
      const array<T, Size> randomStdArray = ZenUnit::RandomStdArray<T, Size>();
      ARE_EQUAL(Size, randomStdArray.size());
   }

   RUN_TEMPLATE_TESTS(RandomStdArrayTests, int, 3)
   THEN_RUN_TEMPLATE_TESTS(RandomStdArrayTests, unsigned long long, 5)
}
