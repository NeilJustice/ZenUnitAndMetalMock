#include "pch.h"

namespace ZenUnit
{
   template<
      template<typename...>
   class SetType, typename T>
   TEMPLATE_TESTS(SetTests, SetType, T)
   AFACT(Contains_ReturnsTrueIfSetContainsElement)
   EVIDENCE

   TEST(Contains_ReturnsTrueIfSetContainsElement)
   {
      SetType<T> s;
      const T element10 = 10;
      const T element20 = 20;

      IS_FALSE(Set::Contains(s, element10));
      IS_FALSE(Set::Contains(s, element20));

      s.insert(element10);
      IS_TRUE(Set::Contains(s, element10));
      IS_FALSE(Set::Contains(s, element20));

      s.insert(element20);
      IS_TRUE(Set::Contains(s, element10));
      IS_TRUE(Set::Contains(s, element20));
   }

   RUN_TEMPLATE_TESTS(SetTests, set, int)
   THEN_RUN_TEMPLATE_TESTS(SetTests, set, unsigned long long)
   THEN_RUN_TEMPLATE_TESTS(SetTests, unordered_set, int)
   THEN_RUN_TEMPLATE_TESTS(SetTests, unordered_set, unsigned long long)
}
