#include "pch.h"

namespace ZenUnit
{
   TESTS(is_span_vTests)
   AFACT(is_span_v_TIsNotAVector_ValueIsFalse)
   AFACT(is_span_v_TIsAVector_ValueIsTrue)
   EVIDENCE

   TEST(is_span_v_TIsNotAVector_ValueIsFalse)
   {
      IS_FALSE(is_span_v<int>);
      IS_FALSE(is_span_v<string>);
   }

   TEST(is_span_v_TIsAVector_ValueIsTrue)
   {
      IS_TRUE(is_span_v<span<int>>);
      IS_TRUE(is_span_v<span<string>>);
   }

   RUN_TESTS(is_span_vTests)
}
