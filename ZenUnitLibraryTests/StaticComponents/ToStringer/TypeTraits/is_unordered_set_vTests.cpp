#include "pch.h"

namespace ZenUnit
{
   TESTS(is_unordered_set_vTests)
   AFACT(is_unordered_set_v_TIsNotAnUnorderedSet_ValueIsFalse)
   AFACT(is_unordered_set_v_TIsAnUnorderedSet_ValueIsTrue)
   EVIDENCE

   TEST(is_unordered_set_v_TIsNotAnUnorderedSet_ValueIsFalse)
   {
      IS_FALSE(is_unordered_set_v<int>);
      IS_FALSE(is_unordered_set_v<vector<int>>);

      IS_FALSE((is_unordered_set_v<set<int>>));
      IS_FALSE((is_unordered_set_v<set<string>>));
   }

   TEST(is_unordered_set_v_TIsAnUnorderedSet_ValueIsTrue)
   {
      IS_TRUE((is_unordered_set_v<unordered_set<int>>));
      IS_TRUE((is_unordered_set_v<unordered_set<string>>));
   }

   RUN_TESTS(is_unordered_set_vTests)
}
