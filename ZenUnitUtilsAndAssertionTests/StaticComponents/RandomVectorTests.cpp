#include "pch.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATE_TESTS(RandomVectorTests, T)
   FACTS(RandomVectorWithSize_DoesSo)
   AFACT(RandomVector_DoesSo)
   AFACT(RandomNonEmptyVector_DoesSo)
   AFACT(RandomSharedPtrVector_DoesSo)
   AFACT(RandomSharedPtrToCharsVector_DoesSo)
   EVIDENCE

   TEST1X1(RandomVectorWithSize_DoesSo,
      size_t size,
      0ULL,
      1ULL,
      5ULL)
   {
      const vector<T> randomVectorWithSize = ZenUnit::RandomVectorWithSize<T>(size);
      ARE_EQUAL(size, randomVectorWithSize.size());
   }

   TEST(RandomVector_DoesSo)
   {
      const vector<T> randomVector = ZenUnit::RandomVector<T>();
      IS_TRUE(randomVector.size() <= 3);
   }

   TEST(RandomNonEmptyVector_DoesSo)
   {
      const vector<T> randomNonEmptyVector = ZenUnit::RandomNonEmptyVector<T>();
      IS_TRUE(randomNonEmptyVector.size() >= 1 && randomNonEmptyVector.size() <= 3);
   }

   TEST(RandomSharedPtrVector_DoesSo)
   {
      const shared_ptr<vector<T>> randomSharedPtrVector = ZenUnit::RandomSharedPtrVector<T>();
      IS_TRUE(randomSharedPtrVector->size() <= 3);
   }

   TEST(RandomSharedPtrToCharsVector_DoesSo)
   {
      const shared_ptr<vector<char>> randomSharedPtrToCharsVector = ZenUnit::RandomSharedPtrToCharsVector();
      IS_TRUE(randomSharedPtrToCharsVector->size() <= 2);
   }

   RUN_TEMPLATE_TESTS(RandomVectorTests, int)
   THEN_RUN_TEMPLATE_TESTS(RandomVectorTests, string)
}
