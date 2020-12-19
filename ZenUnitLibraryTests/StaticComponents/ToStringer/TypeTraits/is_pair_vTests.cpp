#include "pch.h"

namespace ZenUnit
{
   TESTS(is_pair_vTests)
   AFACT(is_pair_v_TIsNotAPair_ValueIsFalse)
   AFACT(is_pair_v_TIsAPair_ValueIsTrue)
   EVIDENCE

   TEST(is_pair_v_TIsNotAPair_ValueIsFalse)
   {
      IS_FALSE(is_pair_v<int>);
      IS_FALSE(is_pair_v<string>);
      IS_FALSE(is_pair_v<tuple<int COMMA int>>);
   }

   TEST(is_pair_v_TIsAPair_ValueIsTrue)
   {
      IS_TRUE(is_pair_v<pair<int COMMA int>>);
      IS_TRUE(is_pair_v<pair<int COMMA string>>);
      IS_TRUE(is_pair_v<pair<double COMMA char>>);
   }

   RUN_TESTS(is_pair_vTests)
}
