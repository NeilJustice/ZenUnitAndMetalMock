#include "pch.h"

TESTS(is_pairTests)
AFACT(is_pair_TIsNotAPair_ValueIsFalse)
AFACT(is_pair_TIsAPair_ValueIsTrue)
EVIDENCE

TEST(is_pair_TIsNotAPair_ValueIsFalse)
{
   IS_FALSE(is_pair<int>::value);
   IS_FALSE(is_pair<string>::value);
   IS_FALSE(is_pair<tuple<int COMMA int>>::value);
}

TEST(is_pair_TIsAPair_ValueIsTrue)
{
   IS_TRUE(is_pair<pair<int COMMA int>>::value);
   IS_TRUE(is_pair<pair<int COMMA string>>::value);
   IS_TRUE(is_pair<pair<double COMMA char>>::value);
}

RUN_TESTS(is_pairTests)
