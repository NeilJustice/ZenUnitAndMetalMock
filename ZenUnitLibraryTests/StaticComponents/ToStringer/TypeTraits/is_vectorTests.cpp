#include "pch.h"

namespace ZenUnit
{
   TESTS(is_vectorTests)
   AFACT(is_vector_TIsNotAVector_ValueIsFalse)
   AFACT(is_vector_TIsAVector_ValueIsTrue)
   EVIDENCE

   TEST(is_vector_TIsNotAVector_ValueIsFalse)
   {
      IS_FALSE(is_vector<int>::value);
      IS_FALSE(is_vector<string>::value);
   }

   TEST(is_vector_TIsAVector_ValueIsTrue)
   {
      IS_TRUE(is_vector<vector<int>>::value);
      IS_TRUE(is_vector<vector<string>>::value);
   }

   RUN_TESTS(is_vectorTests)
}
