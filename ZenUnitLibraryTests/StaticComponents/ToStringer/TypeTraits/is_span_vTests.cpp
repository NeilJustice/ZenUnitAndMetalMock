#include "pch.h"

namespace ZenUnit
{
   TESTS(is_span_vTests)
   AFACT(is_span_v_TIsNotAConstantSpan_ValueIsFalse)
   AFACT(is_span_v_TIsAConstantSpan_ValueIsTrue)
   EVIDENCE

   TEST(is_span_v_TIsNotAConstantSpan_ValueIsFalse)
   {
      IS_FALSE(is_const_span_v<int>);
      IS_FALSE(is_const_span_v<string>);
      IS_FALSE(is_const_span_v<span<int>>);
   }

   TEST(is_span_v_TIsAConstantSpan_ValueIsTrue)
   {
      IS_TRUE(is_const_span_v<span<const int>>);
      IS_TRUE(is_const_span_v<span<const string>>);
   }

   RUN_TESTS(is_span_vTests)
}
