#include "pch.h"

TESTS(is_unordered_mapTests)
AFACT(is_unordered_map_TIsNotAnUnorderedMap_ValueIsFalse)
AFACT(is_unordered_map_TIsAnUnorderedMap_ValueIsTrue)
EVIDENCE

TEST(is_unordered_map_TIsNotAnUnorderedMap_ValueIsFalse)
{
   IS_FALSE(is_unordered_map<int>::value);
   IS_FALSE(is_unordered_map<vector<int>>::value);

   IS_FALSE((is_unordered_map<map<int, int>>::value));
   IS_FALSE((is_unordered_map<map<string, double>>::value));
}

TEST(is_unordered_map_TIsAnUnorderedMap_ValueIsTrue)
{
   IS_TRUE((is_unordered_map<unordered_map<int, int>>::value));
   IS_TRUE((is_unordered_map<unordered_map<string, double>>::value));
}

RUN_TESTS(is_unordered_mapTests)
