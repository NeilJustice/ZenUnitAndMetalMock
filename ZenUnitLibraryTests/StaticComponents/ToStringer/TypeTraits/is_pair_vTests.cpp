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
      using TupleIntInt = tuple<int, int>;
      IS_FALSE(is_pair_v<TupleIntInt>);
   }

   TEST(is_pair_v_TIsAPair_ValueIsTrue)
   {
      using PairIntInt = pair<int, int>;
      IS_TRUE(is_pair_v<PairIntInt>);

      using PairIntString = pair<int, string>;
      IS_TRUE(is_pair_v<PairIntString>);

      using PairDoubleChar = pair<double, char>;
      IS_TRUE(is_pair_v<PairDoubleChar>);
   }

   RUN_TESTS(is_pair_vTests)
}
