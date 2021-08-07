#include "pch.h"

namespace ZenUnit
{
   TESTS(is_unordered_map_vTests)
   AFACT(is_unordered_map_v_TIsNotAnUnorderedMap_ValueIsFalse)
   AFACT(is_unordered_map_v_TIsAnUnorderedMap_ValueIsTrue)
   EVIDENCE

   TEST(is_unordered_map_v_TIsNotAnUnorderedMap_ValueIsFalse)
   {
      IS_FALSE(is_unordered_map_v<int>);
      IS_FALSE(is_unordered_map_v<vector<int>>);

      IS_FALSE((is_unordered_map_v<map<int, int>>));
      IS_FALSE((is_unordered_map_v<map<string, double>>));
   }

   TEST(is_unordered_map_v_TIsAnUnorderedMap_ValueIsTrue)
   {
      IS_TRUE((is_unordered_map_v<unordered_map<int, int>>));
      IS_TRUE((is_unordered_map_v<unordered_map<string, double>>));
   }

   RUN_TESTS(is_unordered_map_vTests)
}
