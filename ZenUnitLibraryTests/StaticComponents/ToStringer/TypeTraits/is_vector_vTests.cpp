#include "pch.h"

namespace ZenUnit
{
   TESTS(is_vector_vTests)
   AFACT(is_vector_v_TIsNotAVector_ValueIsFalse)
   AFACT(is_vector_v_TIsAVector_ValueIsTrue)
   EVIDENCE

   TEST(is_vector_v_TIsNotAVector_ValueIsFalse)
   {
      IS_FALSE(is_vector_v<int>);
      IS_FALSE(is_vector_v<string>);
   }

   TEST(is_vector_v_TIsAVector_ValueIsTrue)
   {
      IS_TRUE(is_vector_v<vector<int>>);
      IS_TRUE(is_vector_v<vector<string>>);
   }

   RUN_TESTS(is_vector_vTests)
}
